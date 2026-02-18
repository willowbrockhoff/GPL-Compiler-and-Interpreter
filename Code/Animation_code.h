#ifndef ANIMATION_CODE_H
#define ANIMATION_CODE_H

#include <set>
#include <string>
#include "types_and_ops.h"

class Game_object;
class Statement;
class Animation_code {
  public:
    //ctor called in the forward declaration production
    Animation_code(const std::string& block_name, gamelang::Type parameter_type);
    void set_parameter_name(const std::string& pname);
    void set_block(const Statement* blk);
    std::string get_block_name() const;
    gamelang::Type get_parameter_type() const;
    void execute(Game_object* argument) const;
    static std::set<std::string> defined_blocklist;
    static std::set<std::string> declared_blocklist;
    static std::set<std::string> used_blocklist;
  private:
    std::string block_name;
    std::string parameter_name;
    gamelang::Type parameter_type;//RECTANGLE, CIRCLE, etc.
    const Statement* block;

    Animation_code(const Animation_code &) = delete;
    const Animation_code &operator=(const Animation_code &) = delete;
};

#endif
