FROM alpine:3.21.2
RUN  apk add musl-dev git gcc make xorg-server libxext-dev libbsd-dev

WORKDIR /home/app

RUN git clone https://github.com/eel-brah/fdf.git

WORKDIR /home/app/fdf

RUN make

CMD ["sh", "-c", "./fdf maps/42.fdf; exec sh"]
