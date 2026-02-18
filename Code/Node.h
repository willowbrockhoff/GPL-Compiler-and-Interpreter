#ifndef NODE_H
#define NODE_H
#include "Expression.h"
#include <iostream>
struct Node {
        std::string name;
        const Expression* value;
        Node* next;

        Node(std::string node_name, const Expression* node_value) :
          name(node_name), value(node_value), next(nullptr) {}
};
#endif