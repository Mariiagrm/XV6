FROM ubuntu

RUN echo 'set auto-load safe-path /' > /root/.gdbinit
RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y apt-utils git build-essential gcc-multilib gdb-multiarch \
        libc6-dev-i386 \
        qemu-system-x86 \
        emacs-nox \
        locales screen tmux vim wget unzip \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*

RUN locale-gen es_ES.UTF-8
ENV LANG es_ES.UTF-8
ENV LC_ALL es_ES.UTF-8

VOLUME ["/root/aso"]
WORKDIR "/root"
ENTRYPOINT ["/bin/bash"]