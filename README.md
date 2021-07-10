# ReLF Native Service

The Android native service for **ReLF: Scalable Remote Live Forensics for Android**.

## Prerequisites

1. Compiled system variant [ReLF client](https://github.com/nexus-lab/relf-client) APK

2. Meet the hardware requirements listed at
   https://source.android.com/setup/build/requirements#hardware-requirements.

3. Docker engine for a more convenient and stable building experience

## Download

1. Change to current directory to where you want to put all AOSP source code
   and output files.
   Make sure it meets the space requirements in the prerequiste section.

2. Create a new docker container for executing download commands interactively.
   Use `latest` as docker image tag when building Android 8.0 or above.
   Use `trusty` when building Android 5.0 to 7.1.

   ```shell
   docker run \
       --name relf-aosp-builder \
       --rm -it \
       -v $(pwd):/aosp \
       ghcr.io/nexus-lab/relf-aosp-builder:<tag> \
       /bin/bash
   ```

3. Initialize the AOSP repo from the [relf-aosp-manifest](https://github.com/nexus-lab/relf-aosp-manifest)
   with your desired branch name, e.g., `android-9.0.0_r30`:

   ```shell
   repo init -u https://github.com/nexus-lab/relf-aosp-manifest -b android-9.0.0_r30 --depth 1
   ```

4. Download the Android source tree:

   ```shell
   repo sync -c -j$(nproc --all)
   ```

5. Copy the built ReLF client APK to `vendor/relf/priv-app/ReLF.apk`.
   Make sure it is compiled in the `system` variant and signed with the AOSP platform keys,
   which is the default behavior.
   Refer to [ReLF client](https://github.com/nexus-lab/relf-client) for build instructions.

6. Exit the container:

   ```shell
   exit
   ```

## Build

1. Create a new docker container for executing build commands interactively:

   ```shell
   docker run \
       --name relf-aosp-builder \
       --rm -it \
       -v $(pwd):/aosp \
       ghcr.io/nexus-lab/relf-aosp-builder:<tag> \
       /bin/bash
   ```

2. Initialize the environment with the envsetup.sh script inside container:

   ```shell
   source build/envsetup.sh
   ```

3. Choose the build target:

   ```shell
   lunch aosp_x86_64-eng
   ```

4. Build the AOSP image:

   ```shell
   m -j$(nproc --all)
   ```

5. Exit the container:

   ```shell
   exit
   ```

## Run

1. Copy the following files from AOSP build to the ReLF image directory.
   The destination path is given behind the arrow for each file.
   `$SDK_VERSION` should be replaced with the Android SDK version of the build.
   For example, `$SDK_VERSION` for the `android-9.0.0_r30` build is `28`.

   - In Android 8.0, 8.1, and 9.0 builds:

      - out/target/product/generic_x86_64/**system/build.prop** -> $HOME/.relf/image/$SDK_VERSION/**system/build.prop**
      - out/target/product/generic_x86_64/**advancedFeatures.ini** -> $HOME/.relf/image/$SDK_VERSION/**advancedFeatures.ini**
      - out/target/product/generic_x86_64/**cache.img** -> $HOME/.relf/image/$SDK_VERSION/**cache.img**
      - out/target/product/generic_x86_64/**encryptionkey.img** -> $HOME/.relf/image/$SDK_VERSION/**encryptionkey.img**
      - out/target/product/generic_x86_64/**kernel-ranchu** -> $HOME/.relf/image/$SDK_VERSION/**kernel-ranchu**
      - out/target/product/generic_x86_64/**ramdisk.img** -> $HOME/.relf/image/$SDK_VERSION/**ramdisk.img**
      - out/target/product/generic_x86_64/**system-qemu.img** -> $HOME/.relf/image/$SDK_VERSION/**system.img**
      - out/target/product/generic_x86_64/**userdata.img** -> $HOME/.relf/image/$SDK_VERSION/**userdata.img**
      - out/target/product/generic_x86_64/**vbmeta.img** -> $HOME/.relf/image/$SDK_VERSION/**vbmeta.img** (if available)
      - out/target/product/generic_x86_64/**vendor-qemu.img** -> $HOME/.relf/image/$SDK_VERSION/**vendor.img**
   
   - In Android 5.0, 5.1, 6.0, 7.0 and 7.1 builds:

      - out/target/product/generic_x86_64/**system/build.prop** -> $HOME/.relf/image/$SDK_VERSION/**system/build.prop**
      - out/target/product/generic_x86_64/**cache.img** -> $HOME/.relf/image/$SDK_VERSION/**cache.img**
      - prebuilts/qemu-kernel/x86_64/**kernel-qemu** -> $HOME/.relf/image/$SDK_VERSION/**kernel-qemu**
      - out/target/product/generic_x86_64/**ramdisk.img** -> $HOME/.relf/image/$SDK_VERSION/**ramdisk.img**
      - out/target/product/generic_x86_64/**system.img** -> $HOME/.relf/image/$SDK_VERSION/**system.img**
      - out/target/product/generic_x86_64/**userdata.img** -> $HOME/.relf/image/$SDK_VERSION/**userdata.img**
   
   Then, copy the device configuration from this repo to the image directory as well:

      - patches/$SDK_VERSION/**config.ini** -> $HOME/.relf/image/$SDK_VERSION/**config.ini**

2. To run the emulator, make sure you have the right dependencies installed and KVM enabled.
   For Ubuntu 18.10 or later, this can be done using:

   ```shell
   sudo apt update
   sudo apt install libc6 libncurses5 libstdc++6 qemu-kvm libvirt-daemon-system libvirt-clients bridge-utils
   ```

3. You can now use the `relf-avd-manager` script under the `scripts` directory of this repo
   to create and run the emulators.
   For example, to run your build, use the following command:

   ```shell
   ./scripts/relf-avd-manager create $SDK_VERSION android-$SDK_VERSION
   ./scripts/relf-avd-manager start android-$SDK_VERSION
   ```

## Tips

1. In AOSP 8.0 and 8.1 builds, the system settings app will not work in emulators due to the
   absence of WiFi P2P service.
   Apply the following patch to fix the app.

   ```shell
   cd packages/apps/Settings && git apply ../../../vendor/relf/patches/27/platform-packages-apps-Settings.patch && cd -
   ```

2. [AOSP 8.0 emulator is broken](https://issuetracker.google.com/issues/66066209) in the default
   configuration.
   Apply the patches in `patches/8.0` to your AOSP source code to fix it.
   Also, you must replace your `kernel-ranchu` in Android 8.0 with the one from the Android 8.1 build.

   ```shell
   cd build/make && git apply ../../vendor/relf/patches/26/platform-build-make.patch && cd -
   cd device/generic/goldfish-opengl && git apply ../../../vendor/relf/patches/26/platform-device-generic-goldfish-opengl.patch && cd -
   cd device/generic/goldfish && git apply ../../../vendor/relf/patches/26/platform-device-generic-goldfish.patch && cd -
   cd frameworks/native && git apply ../../vendor/relf/patches/26/platform-frameworks-native.patch && cd -
   cd hardware/ril && git apply ../../vendor/relf/patches/26/platform-hardware-ril.patch && cd -
   cd packages/apps/Settings && git apply ../../../vendor/relf/patches/26/platform-packages-apps-Settings.patch && cd -
   cd system/core && git apply ../../vendor/relf/patches/26/platform-system-core.patch && cd -
   ```

3. [A bug](https://issuetracker.google.com/issues/37047668) prevents emulators for AOSP 5.0, 5.1, 
   and 6.0 from booting.
   Copy everything under `patches/$SDK_VERSION/bios` to `$HOME/.relf/image/$SDK_VERSION/bios` and recreate
   the virtual devices will fix this issue.

   - patches/$SDK_VERSION/**bios** -> $HOME/.relf/image/$SDK_VERSION/**bios**

4. You can later update your ReLF client and install it to your AOSP system without the need
   of rebuilding the system image, as long as you sign the client APK with the same platform
   keys.

5. If for any reason you changed your AOSP platform keys, please convert your platform
   signing key to Java keystore and sign the client APK with it.
   The platform certificate and private key can be found at:

   ```
   <path/to/aosp>/build/target/product/security/platform.pk8
   <path/to/aosp>/build/target/product/security/platform.x509.pem
   ```

   To convert the certificate and private key to Java keystore, use:

   ```shell
   openssl pkcs8 -in platform.pk8 -inform DER -outform PEM -out platform.priv.pem -nocrypt
   openssl pkcs12 -export -in platform.x509.pem -inkey platform.priv.pem -out platform.pk12 -name aosp
   keytool -importkeystore -destkeystore platform.jks -srckeystore platform.pk12 -srcstoretype PKCS12 -srcstorepass nexuslab -alias aosp
   ```

   Then, add signing configurations to your ReLF client's `mobile/build.gradle`:

   ```groovy
   signingConfigs {
      key{
         keyAlias '<your signing key\'s alias>'
         keyPassword '<your signing key\'s password>'
         storeFile file('</path/to/your/keystore/directory>/platform.jks')
         storePassword '<your keystore\'s password>'
      }
   }
   buildTypes {
      debug{
         signingConfig signingConfigs.key
      }
   }
   ```
