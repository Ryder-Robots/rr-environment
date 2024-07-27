# Rapsberry pi emulator for docker

FROM dtcooper/raspberrypi-os:bookworm

ENV PASSWORD=CHANGETHIS

RUN apt-get update && apt-get upgrade

COPY setup.bash /tmp
COPY ssh/config /tmp/config
COPY id_rsa /tmp/id_rsa

RUN chmod +x /tmp/setup.bash
RUN /tmp/setup.bash ${PASSWORD}

# cmake \
# ffmpeg \
# liblapack-dev \
# wiringpi-dev \
# libjxl-dev \
# libavdevice-dev libavfilter-dev libavformat-dev \
# libavcodec-dev libswresample-dev libswscale-dev \
# libavutil-dev

# libopenblas-dev \

# RUN apt-get install -y ${PACKAGES}