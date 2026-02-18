#include<memory>
#include "Scope_manager.h"
#include "Animation_code.h"
#include "Statement.h"

std::set<std::string> Animation_code::defined_blocklist;
std::set<std::string> Animation_code::declared_blocklist;
std::set<std::string> Animation_code::used_blocklist;

Animation_code::Animation_code(const std::string& block_name, gamelang::Type parameter_type) 
  :block_name(block_name), parameter_type(parameter_type), block(new NullStatement) 
{}
void Animation_code::set_block(const Statement* blk) //in animation_block:
{ delete block; block=blk; }

std::string Animation_code::get_block_name() const
{
  return block_name;
}
gamelang::Type Animation_code::get_parameter_type() const
{ return parameter_type; }

void Animation_code::set_parameter_name(const std::string& pname)//in animation_declaration:
{ parameter_name=pname; }

void Animation_code::execute(Game_object* argument) const
{
  //Implemented in P6
}
