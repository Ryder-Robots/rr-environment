# Rapsberry pi emulator for docker

FROM dtcooper/raspberrypi-os:bookworm

ENV PASSWORD=CHANGETHIS
ENV RSA_LOCATION=/Users/newuser/.ssh

RUN apt-get update && apt-get upgrade

COPY setup.bash /tmp
COPY ssh/config /tmp/config
COPY id_rsa /tmp/id_rsa
COPY files/* /tmp/

RUN chmod +x /tmp/setup.bash
RUN /tmp/setup.bash ${PASSWORD}

RUN service ssh start
EXPOSE 22
CMD ["/usr/sbin/sshd","-D"]
