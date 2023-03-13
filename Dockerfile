FROM ubuntu:20.04
RUN apt-get update && apt-get upgrade -y
RUN apt install qt5-qmake -y
RUN apt install cmake -y
RUN apt-get install qt5-default -y
RUN apt install qtbase5-dev -y
RUN apt install libqt5sql5-psql -y
RUN apt install build-essential -y
RUN apt-get install postgresql -y
COPY . /home/server
WORKDIR /home/server/server
RUN rm -f *moc
RUN rm -f Makefile
RUN qmake server_peresdacha.pro
RUN make
RUN make install
CMD ["./server_peresdacha"]