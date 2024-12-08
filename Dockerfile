FROM ghcr.io/gokiburisoldier/zshenv:latest 
WORKDIR /root
COPY lib ./lib
COPY include ./include

RUN ["apk","add","gcc","g++"]
RUN echo "","alias g++='g++ -l/root/include '"

CMD ["/bin/zsh"]

