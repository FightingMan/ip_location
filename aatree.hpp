/**
 * Description
 *
 * @file aatree.hpp
 * @date 2014-10-09 23:56:00
 * @author FightingMan <gianjason@gmail.com>
 * @copyright (c) 2014 FightingMan.
 */
#ifndef _AATREE_HPP
#define _AATREE_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdio>

namespace HPHP {

    /* {{{ class AATree */
    class AATree {
        public:
            AATree();
            ~AATree();
            struct ipLocation {
                uint64_t start;
                uint64_t end;
                std::string country;
                std::string province;
                std::string area;
                std::string city;
                std::string isp;
            };
            struct node {
                ipLocation* key;
                int  level;
                node *right;
                node *left;
                node *parent;
            };
            int lookup(const std::string &);
            node *search(const std::string &);
            int countnode();
            void makeEmpty();

        private:
            node *root;
            int count;
            uint64_t ip_str2long(const char*);
            void ip_trim(char*);
            void skew(node *);
            bool split(node *);
            void rebal(node *);
            node *insert(node *, node *);
            void print(node *);
            void makeEmpty(node *);

    };
    /* }}} */
}
#endif
/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
