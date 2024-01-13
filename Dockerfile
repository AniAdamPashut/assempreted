FROM archlinux

WORKDIR /app

COPY . /app

RUN pacman -Syu --noconfirm && \
    pacman -S --noconfirm gcc make

RUN bash

RUN make init

RUN make release

CMD ["./assempreter"]