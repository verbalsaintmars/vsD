/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _CHILD_GFLAGS_HPP
#define _CHILD_GFLAGS_HPP
#include "child_include.hpp"

//#define STRIP_FLAG_HELP 1    // Remove GFlag Help String in binary
#include <gflags/gflags.h>

/*
 * Define GFlag here
 */
DEFINE_uint64(vsdSessionid, 0, "SessionID of vsD");
DEFINE_string(soname, "none", ".so file name");
DEFINE_int32(sonameHash, 0, ".so file name hash");
DEFINE_string(sonameVersion, "none", ".so file version");
DEFINE_int32(status, 0, "Standalone:0, Report:1, Heartbeat:2");
DEFINE_int32(lease, 0, "Unlimit:0, minimum: 1sec, maximum: (2^31)-1sec");
DEFINE_int32(preserved, 0, "Preserved argument");

/*
 * Register validator
 */
class vsDGFlag
{
public:
   vsDGFlag();
public:
   static bool ValidateSession(const char* flagname, ::google::uint64 value) {
      UNUSED(flagname);
      UNUSED(value);
      return true;
      //printf("Invalid value for --%s: %d\n", flagname, (int)value);
   }


   static bool ValidateSoname(const char* flagname, const std::string& value) {
      UNUSED(flagname);
      UNUSED(value);
      return true;
      //printf("Invalid value for --%s: %d\n", flagname, (int)value);
   }


   static bool ValidateSonameHash(const char* flagname, ::google::int32 value) {
      UNUSED(flagname);
      UNUSED(value);
      return true;
      //printf("Invalid value for --%s: %d\n", flagname, (int)value);
   }


   static bool ValidateSonameVersion(const char* flagname, const std::string& value) {
      UNUSED(flagname);
      UNUSED(value);
      return true;
      //printf("Invalid value for --%s: %d\n", flagname, (int)value);
   }


   static bool ValidateStatus(const char* flagname, ::google::int32 value) {
      UNUSED(flagname);
      UNUSED(value);
      return true;
      //printf("Invalid value for --%s: %d\n", flagname, (int)value);
   }


   static bool ValidateLease(const char* flagname, ::google::int32 value) {
      UNUSED(flagname);
      UNUSED(value);
      return true;
      //printf("Invalid value for --%s: %d\n", flagname, (int)value);
   }


   static bool ValidatePreserved(const char* flagname, ::google::int32 value) {
      UNUSED(flagname);
      UNUSED(value);
      return true;
   }


private:
};


vsDGFlag::vsDGFlag()
{
   using namespace google;
   RegisterFlagValidator(&FLAGS_vsdSessionid, &vsDGFlag::ValidateSession);
   RegisterFlagValidator(&FLAGS_soname, &vsDGFlag::ValidateSoname);
   RegisterFlagValidator(&FLAGS_sonameHash, &vsDGFlag::ValidateSonameHash);
   RegisterFlagValidator(&FLAGS_sonameVersion, &vsDGFlag::ValidateSonameVersion);
   RegisterFlagValidator(&FLAGS_status, &vsDGFlag::ValidateStatus);
   RegisterFlagValidator(&FLAGS_lease, &vsDGFlag::ValidateLease);
   RegisterFlagValidator(&FLAGS_preserved, &vsDGFlag::ValidatePreserved);
}

#endif // for #ifndef _CHILD_GFLAGS_HPP
