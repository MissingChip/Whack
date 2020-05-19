#pragma once

#include "brick.h"

class Fold : public Brick {
public:
    Fold();
    Fold(int opt);
    virtual ~Fold();

    int drag = 0;
    int dir = -1;
    bool created;
    static glm::vec2 trigger;
    glm::vec2 trigger_pos;
    glm::vec2 anchor_pos;
    glm::vec2 psize;
    glm::vec2 pmouse_pos;
    Brick* temp_brick = nullptr;
    virtual void update();
    virtual void remove(Brick* b);
    virtual void remove(uint idx);

    virtual void clicked(glm::vec2 pos, int button);
    virtual void mouse(glm::vec2 pos);
    virtual void released(glm::vec2 pos, int button);

    Brick* current_empty();
    Brick* new_empty();
    void trash_empty(Brick*);
    void delete_empty(Brick*);
    void swap_live_fold(uint idx);
    void defer_fold(Fold* f);
    bool dir_unset();
};