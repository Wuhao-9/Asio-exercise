#include "struct_header.h"
#include <sstream>

/**
 * @brief 将属性树中的内容转换为json-string
 * 
 * @param tree target property_tree
 */
const std::string property_tree2jsonString(const ptree& tree) {
    std::ostringstream oss;
    boost::property_tree::json_parser::write_json(oss, tree, false);
    return oss.str();
}
