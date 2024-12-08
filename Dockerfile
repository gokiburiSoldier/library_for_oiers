FROM ubuntu
WORKDIR /root
COPY lib ./lib
COPY include ./include
COPY sources.list .

RUN cat ./sources.list > /etc/apt/sources.list

RUN apt-get update
RUN apt install -y g++ gcc vim
RUN echo "" "alias g++='g++ -I/root/include '">>.bashrc

CMD ["/bin/bash"]

