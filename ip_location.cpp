/**
 * Description
 *
 * @file ip_location.cpp
 * @date 2014-10-09 23:56:37
 * @author FightingMan <gianjason@gmail.com>
 * @copyright (c) 2014 FightingMan.
 */
#include "ip_location.hpp"

namespace HPHP {

    /* {{{ static Array HHVM_FUNCTION(ip_location, const String& longip) */
    static Array HHVM_FUNCTION(ip_location, const String& longip)  {

        AATree::node *temp = s_ip_location_extension.at->search(std::string(longip.c_str()));
        Array return_value = Array::Create();
        if (temp) {
            return_value.set(StaticString("country"), Variant(temp->key->country)); 
            return_value.set(StaticString("province"), Variant(temp->key->province)); 
            return_value.set(StaticString("area"), Variant(temp->key->area)); 
            return_value.set(StaticString("city"), Variant(temp->key->city)); 
            return_value.set(StaticString("isp"), Variant(temp->key->isp)); 
        }
        return return_value;
    }
    /* }}} */

    /* {{{ static int64_t HHVM_FUNCTION(ip_count) */
    static int64_t HHVM_FUNCTION(ip_count) {
        return s_ip_location_extension.at->countnode(); 
    }
    /* }}} */

    /* {{{ void ip_locationExtension::moduleInit() */
    void ip_locationExtension::moduleInit() {
        HHVM_FE(ip_location);
        HHVM_FE(ip_count);
        loadSystemlib();
    }
    /* }}} */

    /* {{{ void ip_locationExtension::moduleLoad(const IniSetting::Map& ini, Hdf hdf) */
    void ip_locationExtension::moduleLoad(const IniSetting::Map& ini, Hdf hdf) {
        std::string path = hdf["ext_conf"]["ip_location"]["path"].configGetString("ip.dict");
        std::ifstream fin(path);
        std::string line;
        at = new AATree;
        while (std::getline(fin, line)) {
            at->lookup(line);
        }
        fin.close();
    }
    /* }}} */

    /* {{{ void ip_locationExtension::moduleShutdown() */
    void ip_locationExtension::moduleShutdown() {
        at->makeEmpty(); 
    }
    /* }}} */

    HHVM_GET_MODULE(ip_location);

}
/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
