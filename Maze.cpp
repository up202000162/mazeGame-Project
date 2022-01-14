#include "Maze.h"

Maze::Maze(Uint numRows, Uint numCols) {
    //construtor
    this->numCols = numCols;
    this->numRows = numRows;
}

Uint Maze::getNumRows() const {
    // retorna quantidade de linhas de que o maze é formado
    return numRows;
}

Uint Maze::getNumCols() const {
    // retorna quantidade de colunas de que o maze é formado
    return numCols;
}

void Maze::addPost(const Post& post) {
    // acrescenta um poste ao vetor de 'Post'
    posts.push_back(post);
}

std::vector<Post> Maze::getPosts() const{
    // retorna vetor de todos os postes
    return posts;
}





