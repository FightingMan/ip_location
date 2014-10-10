/**
 * Description
 *
 * @file ip_location.hpp
 * @date 2014-10-09 23:56:51
 * @author FightingMan <gianjason@gmail.com>
 * @copyright (c) 2014 FightingMan.
 */
#include "hphp/runtime/base/base-includes.h"
#include "aatree.hpp"
namespace HPHP {

    static class ip_locationExtension : public Extension {
        public:
            AATree *at;
            ip_locationExtension() : Extension("ip_location", "0.0.1-dev"){}
            virtual void moduleInit();
            virtual void moduleLoad(const IniSetting::Map& ini, Hdf hdf);
            virtual void moduleShutdown();
    } s_ip_location_extension;
}
/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
