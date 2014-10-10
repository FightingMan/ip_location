/**
 * Description
 *
 * @file aatree.cpp
 * @date 2014-10-09 23:56:21
 * @author FightingMan <gianjason@gmail.com>
 * @copyright (c) 2014 FightingMan.
 */
#include "aatree.hpp"

namespace HPHP {

    AATree::AATree():root(NULL),count(0) {}

    AATree::~AATree() {
        makeEmpty(root);
    }

    /* {{{ void AATree::makeEmpty() */
    void AATree::makeEmpty() {
        makeEmpty(root); 
    }
    /* }}} */

    /* {{{ void AATree::makeEmpty(AATree::node *temp) */
    void AATree::makeEmpty(AATree::node *temp) {
        if (temp) {
            makeEmpty(temp->left); 
            makeEmpty(temp->right); 
            if (temp->key) {
                delete(temp->key);
            }
            delete(temp);
        }
    }
    /* }}} */

    /* {{{ int AATree::lookup(const std::string &line) */
    int AATree::lookup(const std::string &line) {

        std::stringstream ss(line);
        int i = 0;
        AATree::node* temp   = new AATree::node;
        AATree::ipLocation* location = new AATree::ipLocation;
        for (std::string token; std::getline(ss, token, '|'); ++i) {
            switch (i) {
                case 0:
                    location->start = ip_str2long(token.c_str());
                    break;
                case 1:
                    location->end   = ip_str2long(token.c_str());
                    break;
                case 2:
                    location->country = token;
                    break;
                case 3:
                    location->province = token;
                    break;
                case 4:
                    location->area = token;
                    break;
                case 5:
                    location->city = token;
                    break;
                case 6:
                    location->isp = token;
                    break;
                default:
                    break;
            }
        }
        temp->key    = location;
        temp->level  = 1;
        temp->left   = NULL;
        temp->right  = NULL;
        temp->parent = NULL;
        temp         = insert(root, temp);
        return count;
    }
    /* }}} */

    /* {{{ uint64_t AATree::ip_str2long(const char *ip) */
    uint64_t AATree::ip_str2long(const char *ip) {
        int a, b, c, d;
        uint64_t ret = 0;

        ip_trim((char *)ip);
        sscanf(ip, "%d.%d.%d.%d", &a, &b, &c, &d);
        ret = ret | (a << 24);
        ret = ret | (b << 16);
        ret = ret | (c << 8);
        ret = ret | (d);

        return ret;
    }
    /* }}} */

    /* {{{ void AATree::ip_trim(char *str) */
    void AATree::ip_trim(char *str) {
        char *copied = NULL;
        char *tail   = NULL;

        if(str == NULL) {
            return;
        }

        for(copied = str; *str; str++ ) {
            if( *str != ' ' && *str != '\t' ) {
                *copied++ = *str;
                tail = copied;
            } else {
                if(tail) {
                    *copied++ = *str;
                }
            }
        }

        if(tail) {
            *tail = 0;
        } else {
            *copied = 0;
        }
    }
    /* }}} */

    /* {{{ void AATree::skew(AATree::node *temp) */
    void AATree::skew(AATree::node *temp) {

        AATree::node *ptr = temp->left;
        if (temp->parent->left == temp) {
            temp->parent->left = ptr; 
        } else {
            temp->parent->right = ptr; 
        }
        ptr->parent  = temp->parent;
        temp->parent = ptr;
        temp->left   = ptr->right;
        if (temp->left != NULL) {
            temp->left->parent = temp; 
        }
        ptr->right = temp;
        temp->level = temp->left ? temp->left->level + 1 : 1;
    }
    /* }}} */

    /* {{{ bool AATree::split(AATree::node *temp) */
    bool AATree::split(AATree::node *temp) {

        AATree::node *ptr = temp->right; 
        if (ptr && ptr->right && (ptr->right->level == temp->level)) {
            if (temp->parent->left == temp) {
                temp->parent->left = ptr; 
            } else {
                temp->parent->right = ptr; 
            }
            ptr->parent = temp->parent;
            temp->parent = ptr; 
            temp->right = ptr->left;
            if (temp->right != NULL) {
                temp->right->parent = temp; 
            }
            ptr->left = temp;
            ptr->level = temp->level + 1;
            return true;
        }
        return false;
    }
    /* }}} */

    /* {{{ void AATree::rebal(AATree::node *temp) */
    void AATree::rebal(AATree::node *temp) {

        temp->left = NULL; 
        temp->right = NULL; 
        temp->level = 1;
        for (temp = temp->parent; temp != root; temp = temp->parent) {

            if (temp->level != (temp->left ? temp->left->level + 1 : 1)) {
                skew(temp); 
                if (temp->right == NULL) {
                    temp = temp->parent; 
                } else if (temp->level != temp->right->level) {
                    temp = temp->parent; 
                }
            }

            if (temp->parent != root) {
                if (!split(temp->parent))  {
                    break; 
                }
            }
        }
    }
    /* }}} */

    /* {{{AATree::node* AATree::insert(AATree::node *temp, AATree::node *ins) */
    AATree::node* AATree::insert(AATree::node *temp, AATree::node *ins) {

        if (root == NULL) {

            ins->parent = NULL;
            ins->left   = NULL;
            ins->right  = NULL;
            root = ins;
            ++count;
            return root;
        }

        if (ins->key->start < temp->key->end) {
            if (temp->left)  {
                return insert(temp->left, ins);
            }
            ++count;
            temp->left = ins;
            ins->parent = temp;
            rebal(ins);
            return ins;
        } else if (ins->key->start > temp->key->end){
            if (temp->right)  {
                return insert(temp->right, ins);
            }
            ++count;
            temp->right = ins;
            ins->parent = temp;
            rebal(ins);
            return ins;
        } else {
            return ins; 
        }

    }
    /* }}} */

    /* {{{ void AATree::print(AATree::node *temp) */
    void AATree::print(AATree::node *temp) {

        if (!temp) {
            return; 
        }
        print(temp->left);
        //std::cout << "Value: " << temp->key->start << " Count:" << temp->count;
        //std::cout << " Level: " << temp->level << std::endl;
        print(temp->right);
    }
    /* }}} */

    /* {{{ int AATree::countnode() */
    int AATree::countnode() {
        return count;
    }
    /* }}} */

    /* {{{ AATree::AATree::node *AATree::search(const std::string &ip) */
    AATree::AATree::node *AATree::search(const std::string &ip) {

        uint64_t id = ip_str2long(ip.c_str());

        AATree::node *temp = root;
        while (temp != NULL) {
           if (id > temp->key->end) {
                temp = temp->right;  
           } else if (id < temp->key->start) {
                temp = temp->left; 
           } else {
               return temp; 
           }
        }
        return NULL;
    }
    /* }}} */

}

/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
