
#ifndef PROJETO_NOVO_2_MAZE_H
#define PROJETO_NOVO_2_MAZE_H
#include <vector>
#include "Post.h"
typedef unsigned int Uint;

class Maze {
public:
    explicit Maze(Uint numRows = 0, Uint numCols = 0);
    void addPost(const Post& post);
    Uint getNumRows() const;
    Uint getNumCols() const;
    std::vector <Post> getPosts() const;
private:
    Uint numRows, numCols;
    std::vector<Post> posts;
};

#endif //PROJETO_NOVO_2_MAZE_H
