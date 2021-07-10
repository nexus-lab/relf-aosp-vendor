# A docker image for building ReLF AOSP images

FROM ubuntu:focal

LABEL org.opencontainers.image.source https://github.com/nexus-lab/relf-aosp-vendor

WORKDIR /aosp

RUN apt update && \
    DEBIAN_FRONTEND=noninteractive apt install -y \
    git-core \
    gnupg \
    flex \
    bison \
    build-essential \
    zip \
    curl \
    zlib1g-dev \
    gcc-multilib \
    g++-multilib \
    libc6-dev-i386 \
    lib32ncurses5-dev \
    x11proto-core-dev \
    libx11-dev \
    lib32z1-dev \
    libgl1-mesa-dev \
    libxml2-utils \
    xsltproc \
    unzip \
    fontconfig \
    libncurses5 \
    openjdk-8-jdk \
    python-is-python2 && \
    rm -rf /var/lib/apt/lists/*

RUN curl https://storage.googleapis.com/git-repo-downloads/repo-1 > /usr/local/bin/repo && \
    chmod a+x /usr/local/bin/repo

RUN git config --global user.name "ReLF Builder" && \
    git config --global user.email "relf-builder@example.com"

ENV ANDROID_COMPILE_WITH_JACK=false

VOLUME /aosp
