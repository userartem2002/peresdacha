FROM ubuntu:20.04
RUN apt update
RUN apt install qt5-qmake -y
RUN apt install cmake -y
RUN apt install qt5-default -y
RUN apt install build-essential -y
COPY . /home/medhelper_new
WORKDIR /home/medhelper_new
RUN qmake /home/medhelper_new/medhelper_new.pro
RUN make
RUN make install
CMD ["./medhelper"]
