FROM archlinux

WORKDIR /app

COPY . /app

RUN pacman -Syu --noconfirm && \
    pacman -S --noconfirm base-devel

RUN make release

CMD ["./assempreter"]