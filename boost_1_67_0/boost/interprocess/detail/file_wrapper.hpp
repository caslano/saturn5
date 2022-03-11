//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_FILE_WRAPPER_HPP
#define BOOST_INTERPROCESS_DETAIL_FILE_WRAPPER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/detail/simple_swap.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail{

class file_wrapper
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   BOOST_MOVABLE_BUT_NOT_COPYABLE(file_wrapper)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   //!Default constructor.
   //!Represents an empty file_wrapper.
   file_wrapper();

   //!Creates a file object with name "name" and mode "mode", with the access mode "mode"
   //!If the file previously exists, throws an error.
   file_wrapper(create_only_t, const char *name, mode_t mode, const permissions &perm = permissions())
   {  this->priv_open_or_create(ipcdetail::DoCreate, name, mode, perm);  }

   //!Tries to create a file with name "name" and mode "mode", with the
   //!access mode "mode". If the file previously exists, it tries to open it with mode "mode".
   //!Otherwise throws an error.
   file_wrapper(open_or_create_t, const char *name, mode_t mode, const permissions &perm  = permissions())
   {  this->priv_open_or_create(ipcdetail::DoOpenOrCreate, name, mode, perm);  }

   //!Tries to open a file with name "name", with the access mode "mode".
   //!If the file does not previously exist, it throws an error.
   file_wrapper(open_only_t, const char *name, mode_t mode)
   {  this->priv_open_or_create(ipcdetail::DoOpen, name, mode, permissions());  }

   //!Moves the ownership of "moved"'s file to *this.
   //!After the call, "moved" does not represent any file.
   //!Does not throw
   file_wrapper(BOOST_RV_REF(file_wrapper) moved)
      :  m_handle(file_handle_t(ipcdetail::invalid_file()))
   {  this->swap(moved);   }

   //!Moves the ownership of "moved"'s file to *this.
   //!After the call, "moved" does not represent any file.
   //!Does not throw
   file_wrapper &operator=(BOOST_RV_REF(file_wrapper) moved)
   {
      file_wrapper tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Swaps to file_wrappers.
   //!Does not throw
   void swap(file_wrapper &other);

   //!Erases a file from the system.
   //!Returns false on error. Never throws
   static bool remove(const char *name);

   //!Sets the size of the file
   void truncate(offset_t length);

   //!Closes the
   //!file
   ~file_wrapper();

   //!Returns the name of the file
   //!used in the constructor
   const char *get_name() const;

   //!Returns the name of the file
   //!used in the constructor
   bool get_size(offset_t &size) const;

   //!Returns access mode
   //!used in the constructor
   mode_t get_mode() const;

   //!Get mapping handle
   //!to use with mapped_region
   mapping_handle_t get_mapping_handle() const;

   private:
   //!Closes a previously opened file mapping. Never throws.
   void priv_close();
   //!Closes a previously opened file mapping. Never throws.
   bool priv_open_or_create(ipcdetail::create_enum_t type, const char *filename, mode_t mode, const permissions &perm);

   file_handle_t  m_handle;
   mode_t         m_mode;
   std::string    m_filename;
};

inline file_wrapper::file_wrapper()
   : m_handle(file_handle_t(ipcdetail::invalid_file()))
   , m_mode(read_only), m_filename()
{}

inline file_wrapper::~file_wrapper()
{  this->priv_close(); }

inline const char *file_wrapper::get_name() const
{  return m_filename.c_str(); }

inline bool file_wrapper::get_size(offset_t &size) const
{  return get_file_size((file_handle_t)m_handle, size);  }

inline void file_wrapper::swap(file_wrapper &other)
{
   (simple_swap)(m_handle,  other.m_handle);
   (simple_swap)(m_mode,    other.m_mode);
   m_filename.swap(other.m_filename);
}

inline mapping_handle_t file_wrapper::get_mapping_handle() const
{  return mapping_handle_from_file_handle(m_handle);  }

inline mode_t file_wrapper::get_mode() const
{  return m_mode; }

inline bool file_wrapper::priv_open_or_create
   (ipcdetail::create_enum_t type,
    const char *filename,
    mode_t mode,
    const permissions &perm = permissions())
{
   m_filename = filename;

   if(mode != read_only && mode != read_write){
      error_info err(mode_error);
      throw interprocess_exception(err);
   }

   //Open file existing native API to obtain the handle
   switch(type){
      case ipcdetail::DoOpen:
         m_handle = open_existing_file(filename, mode);
      break;
      case ipcdetail::DoCreate:
         m_handle = create_new_file(filename, mode, perm);
      break;
      case ipcdetail::DoOpenOrCreate:
         m_handle = create_or_open_file(filename, mode, perm);
      break;
      default:
         {
            error_info err = other_error;
            throw interprocess_exception(err);
         }
   }

   //Check for error
   if(m_handle == invalid_file()){
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }

   m_mode = mode;
   return true;
}

inline bool file_wrapper::remove(const char *filename)
{  return delete_file(filename); }

inline void file_wrapper::truncate(offset_t length)
{
   if(!truncate_file(m_handle, length)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}

inline void file_wrapper::priv_close()
{
   if(m_handle != invalid_file()){
      close_file(m_handle);
      m_handle = invalid_file();
   }
}

}  //namespace ipcdetail{
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_FILE_WRAPPER_HPP

/* file_wrapper.hpp
QR7Gku9G3gbqtcnebnksjH6Cdp2Q3AyNJ5ZujYpVkdCJ5gg78c+4MYil6mEdhnxFIOzvRl00gG0pKyvqdNcWdQo7o0trMetWrHR7BVZaGxV28krn80oDkIyzT7xCPoT2dA5TwPyYvf2hHBCt94c/Ts6DoZMu1B8sFPtjl8KqoT8UsGH+Beif3px9KF/+9uSrMPZojaIgxk1JIoMV2/KoAE3pJGe0RbxdRZ3PL8E0oSrqqELrkGp8jQptnc9PprL0F5p2CXbF19bprkcsLa3HtB3Yh667sA/1UWEr78PKOupD812IuJDk7kPE7U4eRlzfDyJubbKGuF1/0xCnWqwIOzHZxmGvANhyOyw9HYI5uhQw2tYhtHQ+v5wajH/bm9mtUKYDHZr3dj6/njLW84wplNFA5i21gHxIugS7QDZR7UDaZjb2Ljw0bdXJfZLY7b0ZW9khbGlvPg55V9Hn2y17+jYe1hHE8Kem44KJjbsLlcAgGqX1UVIvG1pGNmexi/FsvLMdjQnIRFN76KWHR4SGqwWzv1nJpjMm1MPCjziarnZw9t6Mby1XO3q1N6KMC5EyHFG9o+82yy53VO8Glv6YNPWF2Bi9mwXML0hJ0n1ngNqAyNuKOA7J3uZ1QuDkZQkIXNEWR5oN0jVEoZ2HYRnRJ76Y2MDSkVj6bOkPYylp2Q9giS09D0sfLP3/hqWMOJZmjcAS8KSYZRhRhtgXOFFQpqSJErI8WvKdRvycIH/8JhDkXpoqOAN2qjPAvxtmwIkl6gxQZ/GjfyUkNy5JnAF/HzkDdkbJu/P3TAJffBL8eQ8aNdGsxCnXpk5VmqGY/xNeT/mShMF8DTPPnw32JT8wGy5fct5ssCwZOc7KnT88zhcu+YFx1i05b5z/fWd8nP8fAAAA//+sfQ98U9XZcNKkJUAgAVpABayKipZtzMAkC7gKXOjUuJRCC8MW5tR1Ge8rvt6LOAnCblO5Hi5URYcTEac4t/Eqjn91ILaW0XZF6JRBkTLr1rlT021RIW2lcL7nec5NmiK+3/f9fu8c6b3n/3nOc57/51zFfbql9mPX4Lhnj+JKPnTSw+PKwRsVt94o8oLtnj01tR+5Btc+Hmy4MeiqbXN59jTi2+Ebg53Jt9WRETZtiKOUm+4XDLvxgDM2ijV5Xg+2OoLxmZ7XS1sdpXHDucGY/MJp5Vhhq7Kx8PSY8bzp9UzbwoV8/A8zbazFKHWfUtyt925svffY6ehSIURLIx8IWaejK+nFUDp5z93wruzAFxfvxJfMhnPDvPju5q3wrkeabSxuaO3qjJP8Lx+dUqpaGj+AvATknVJe9uyJrzlio+Zgnh9AI6ch44NgNUxycJySOvkfIQneY1cAOP6XQeTtA1Ev01pjV6SgdHs/KMX+erpFKHGmxO0aDyg1nvV3nBeCKW0suE7fdhdMwKZvW4J/jGg5/DGjmBYyo3fIP5Pxj3jAaey+B5742NNQOToLHqM1qoPlO0Nidwgz5lzRJcTuAngUOS+/Mcxbr2yeenSYN+YwtM1mcPMhpdfGv/NsQujBXmGa2DifNLpL8GE/zrS947aF51VrM4d5+Y3lsIInjVKuR9xCG6RHvMJT8UyGzcY0lxnZsW3bNjO4Yxv/7AgMQ9ufp+1ikeq8yA5DazUiLZ6KpVAymvBU3AN/zWANP+vtEmymU7+315Yab85SGF4Ic78+qgum4am4EUrr9x6z7cMRG6XNTOFQsrhELHPCuO0iZ5ms0cybL5M1Ouw2m9COCe0gv/PyLuFrhMSnaw2lndVGa7RMfmteQpiKK2QqLSF+DwzWUNqw3ht2mgkO8RV4DEEDImc/tK7fG7fhZNn8Fqa0sj/WKy7ItwGmeirWwoNnT6mXKd5a7lrThFiHePI31+AWSvMm36LvrRrILrC6z39rTn4G2tG77aum6DUXPK+/w76o/UcGO1KSd7TQdFaGeM9LgOIH3XqkNWOVR4+0ZBjjVjqNu27u1Q855SAK6gFnoGvzNgGjybBGA4jMSt0s4q6NuYbgSAgrTw2ug9TamBfe5tBr14dXiGu6meIKKJ2PjvEH45FRecE4TbGenWQXcIhbVAf2VtrpL3VFrqQR5pW62KGSvPpQMS+RI3R03a51wogQIdTr5dKU59oO28LwH8JPa50rtF1C2wHLJXKmATBjExCGQa7fuxXW9WUY93ZT2QqLUQP/dhA2z3+Vz/0A90F7Ci9gLX8GGCm0tiQGN1sYXNoMa08YHHnGwmDAngdyAH3n3kfoy8R81gmTFcvcYpkLBzIJehE5nTuGeUvfcdqqy90jvXVUqqi4hJ3kH58GxNTczBu26Z1e1guIXSQ0F2vYJuYWLC5bVJpsVO8cDRU+9Qn/AdsQwIPov2Ahilipy6xc4QYMYk18AowaqBirvAcS8irvgl/W9GzeO3/qdtCLOWsqbOE9C/BR6Q5x53Do+/9SeAk88pAbC2Kqoz7EKhfIB1OJY68HhqVaScuEjMv711pCJQqgGsfcx/pXS+ZCzl8Hd4k5usjwrLsJqQgAo4kHYYcuWlzWCCBkoqiE9fhO+V/ohjpaMb+Q2SV+DcDwqrexAcXsqKg66IDJxAOfq0NZFjsiqu4A9IXtOLCEH5nWJRZS1tj0LFj5MpUNKKLa+YDiZYt9NYvecUFnxexTsWf1YIBCeXG3oE299PqEYCFn9D01kxVMjTlYweRo48MD2RH+r73dInZZ9D3NAVS8MGwXy3L5Iz/pEayB/+Q/4A90WSa24h5Kb9iTbHgENBwWgM1QbZasNrl/tbCzOjoHyONgZHCfGlqcL/xzt9DXtwEo4E87/vEJ36mZ9VkACSz2084vhnuNA82QYhw4Rr8t9NuKv1s4/XbSb5zSz9AvwtRcnwsYZkR6jQOj8eHAGPjlN6xw2sKDzPXTKGky/U7FjNF/uCBguqzWqKTiW6YOxt9eag9plnGggZ5tlOukmocpxUXPXvrNpl83/q7HDtkhfh7YZl1yS/ne8z/hhJa1TCPkjHnYEy/DCzNexc4KnAZtL1nWwMajjeoI/U2sYFMHARLxXYBLMRc+3bK4Gza8Cyu8uPEh2I8A1VeQ6ez+gQVVCT0513qg/NBIvf3wyeFe/uZ02PQEH6IDeQ85bUgHYO3vP9kt+O044rBa3YjNHcXmTvpE4ENPxQ9wzWfmBuo9FcUZSPBz2vcM8yIrmAOv/n3lg3FPB+gZ4aSOAKxXa2CgTfzJt7pFRy5yMh2X0D9VG2IyXMbCEN/Zeh4YTFtIPJhrRNqMSLsR4UakU+T07h3mLTKDVTwGrK88+66RXniBNeUZ2cinYCDIp14NHAW8e248ILSDNYmqebBzPK/riC9Ma2fBtrz4bEPbbwRb/Psm4LAu90/fVTbSqw2X76vqmD4eF8sWywSSnAdNtppKc8iINPATpd3ixcPQsa40Z+jKsQy/cuxRh6EcY/phmC2C4t8AWNg/ymF80WCB2AoXc/lqosLzdI0RPGxEXkYQLcKc743vqoXiueqtAW2/Ok2ncdg0H1Ma2PxWEALyzbl2Q2kw5rd41t4ANQI6jtBjjsXaT+EoTefPGDCBVkPbkai1q9cwgqdDaQHGAJwiT2+l1zb9kMtQdhladeybbEDYDkS/EIAH/9YWAoEIjWEu7DHf6ZjfZgRXs2CL45AR3G7M32Uo1Sz4MrPr9fNMbTvQ8m0iNIlp1UC1I4c90RFEz17FVVmJtLeJ1x7tFsiOjEiNEQERYCKsGr7DcoqcAsAQ4EbMIbQaXJwqB9KqFVnGvl6i1vzhfd0WF6riCzzAhdoWJzfMRexCdekNouOwZBneIrE8V2KI/8Ax3FJelI1qsoyZbl9NxzYoBdvDUIBruw2lN1AfcQDisEpcNSPiDdSrP2QNQDQnsu+6GG60a8wH5pkRjvNl8zv983tX3syCZ/zB3lVDhQJIrjXHvsm/dTUgmdKbF+w1Nc7OQdm8d7YFale5GXbvnm3MdMay4NkocuoXBLDEmZijcxiVE4YXPg8csiarCMYocg4CZNghYggp9ugG6v2p71RJ4HPN6asBrJqdm9plgON7rwKOHYH9P8NUzoSM0jMGoKcF7zMhAoiEdzfLEtoZdqACycsRCfVAvTbYOLASUjpewI18AEERu4HVR4W6DRg9+055QeZIL38YOPDChQA5gM5g5mUNYu4y6D0rKrT3YUSl3SiAwihsK69GvnaEZ4e6SY4sRelatjHFaqOXTZ+FK1Ta66nIRjEThngixAN1CSg5VeQAE0j1dspT8QSsGv/2OzBJa2PcDmMYuAaINtRVbwGqjLRMfxmKITl7cQkIImFbQSicQXPvhK7Cdr1unsSNOLzSwxl4iE21CnF40V/BhmxELkIL9Ei3Tb3sRdvykQjlATCjOS0JwHGQLrYeOidYsBfQY5T+cK5QB+pvVtmQGruYPWwvFqFcFuyG3Hv4WzvOoRaxCOADSP06vBHonqyRvHkmW4tdBlgBvGtTZF6+ExcAeML8XvVqth4LAL5po4wncIY0XuMZTLVGTayG0LoSF1adaIGzszYFzv0jEZzQoVfsocWnjpD469MPqwBST8UvEXJpk/3+CcDplugpbQDXrsNHq9Vn+lq9L9mqm60dbye+lMFORk+pmDafze/1NR5YDc2CNHE9u41onNOG8nAGPtrx8YiL3Zar9wgtiwVd+hGv2PHqUCBsew959jbWtnkH14bKr0QEIZoBkwWxUQpKQAGm4+zZpyCK4MjkOp6Q+Ku/gkzcZi0oYHJZESH0kjSEfhVkW9YC4z+lBuSSAz6rk9hz67DKKfU66lRuMvUyyUNaYCwok4e9lHkXDADw/+VFi0GK6ThWCFwyb1xCHLa27ZgXO68d6fX9ARAeJGJTafeJEPBgYmTJ/dnetz9h89g90V/gGttTOMnWbwSCGDiqDvY/nKtmlfAZ52ExKglr6tXRQuN6zTyhQTM53mriutG5qICRBDgNMIltmZySapBbT8bcypWSS627Dt4ClUgoPeblqK3Byi+6o1sE6jzRQVjSUYzzboBBdXyBEI24MjzRaBIP5Rj9JCx5Kk7a5FbOwc0d4kvfTmHKtGzEFBgsa5FjhxHDuNMG/TyiMOE6s8Pmk/IXjrciiZdAqBAv3zmWEEUhPrbunIj95MW2scO9fsWl/SCUGo2pdOILSApGJG5EzhiRbskQoHvIS4eVeiMOCWhie5IasvWbEDINQJ17BNC5kQAQ8eQCJIzB3sVlvncX8U23Z9oakwIZ0GWdQGtTB6evGm5GTIY+bgrQjLURck1wd1voGRtFpMrzuuIO20JWdaRWZaUkn8v20yB6+YEURD8Zbu29q0CSfnU7UZmRSHhpZ28ldqpm+mryY4MkOc473i3KUoKk3pndh5yImy72aRqnWJ7rE/0BKAfw7FupAfyYBoCLAnz1l8R9W1hDbBYbgIoG0jfWQkvxoMWPgWmFM8xgZ6FM8hJHctOKuFIros1jH7KjvPK3QCi7YWu9AVTzj9aLOo3aeyjZ3nJsD1KKKenS7QFFrgfWWxfLAKUHl9D3bhk//l1cQQvCCcXtAmLSo82kZuQ839ifmucaVObiAOoEgPoIn46D2VMgybcXEt2BHZtQWUPGPEJo2TB7DQeC0vgPftItFgPQvSk9F+iAT7BPLUlzgX/6RMdIrxqSkoxWkLbWX+8bwgWvBLU6Adb6W3Ktx0qZxZLgpWQslwuWZFCSTCrdKH2+gHtrAUifRrAbt9QGeE/MHG9XRwBd8bBbXaiUPb+NNLVyWBxfgm+gN/Uqf6RX9YCEZD6YlIJQ3uvWtrGZSwzlTOwyKKANZDMX+BLwOtsaTqBLzeX/eBcA5yXNH2ABghGKUKD7P7kVSlArnihKvx3fQ0PZ56P76GYaaqIVoLikiH3K/zDH0iQboSRbMZ4F3YEeT8XTOPuC8az+mlpQlDNA0dAJF4/wjVDBkjve8lib5fvsqC/otrhP0NdoBDuNYNwIngHIIGoCfJc1nxcvzvv+SK+jJvRiSP4lvMtZuhvlCIu8XCxHeH0RNyj2qgu7vvnebpGiF+VzkthGxII4kjo2jXymkT2LYZXVUWFJKmHYZfpWZP22ErGHipK4xvmj0AuxfKuaIcl6t3p1VKxwlcBAXrunW4g9K0nc4y/iS3LAaf0vLpNydQkDGfKBXONNVJeTaPirN1No+NBQC4o3FMNGHy3JmSXIQG8NfA9qI0d4469gi8SjCe102WJJcGAusFMW6qtybWoR0NuqNgcyubDty4C0RDwpxFhjuKZvDJ8PSYkcIOIhqVPtEl5ILGHnAb0E+TorpVFMQI4GcmQSFX6XbMCjr8gVGlo2xlUnRMyLdY9Y+/b3zxGt7DNP9UNIN6v1NRaXXIw7sIkMhVu0SXGZy+aRJuBr3OYv8KpX+4Ne2LTzuf9xUlqGgxZh3O5i+UsM1E8yQfZPYcy3FMQYtwQczgXNI+WZluxBgJkM1K4MlXsW93p5S2GmrXwBGiz2DUqIhawBBuarQf2mQc3kL/0L9pc5N6k+QZv8438LkVBcdnVAMd9LVQ6l84Y0wQX0JLLmoRKOs5Mr8sTe1Ir8AE1h3b4EEKgL6iD2GAqCgUPAqpt49P2EKC63t8Hg74bVAABJIQ4KTjeA53axSouQXimWLS1fewaaG+7G9WFHDKWdr95mIdIJFmwH4RKka1G1xJEyL49BiNiho+nnhQjb+cO6EPo+koYXqqNB0a5AkcUynHVD4Y5PUITZh4YgIBR/slmCpZzTW3tSczIH45wATQTg4V4cY3n+YEAebbCFPCNRbvAWIf51o7QIAgwS1WI+bS5QKeh4Db4BI5tSj9Ra09iQqShaN6qDinnGi72Y9oM1h2xeIar/TQBjTVck+Lz3EsLXONvzdC2afV1raodBXiHBDUVNc+9+L8znFhjWeED+o7znQTuW06/Dl2HL7baY+8UlD6MIrzqMZaDBcJs2UB9yDwgZIubBMTfx62/tFi9hik7GGBDbHusPh927U3CIDrLm+yO2g1YqoZbqq5ba1BJAcHYLCC3G7FyulZA57+8LegRKSz/fj/QdsK/TUOLAFGDzIc2EjZbTdF5IAspmL6VZxUkukM+4+4u4awJ0CZNrYnF+3zlBBkIRWpLaG5fPSOPdF4nY7FNo23eKpD+yAtZXojWBGGRpp1EaT6rGZB4YSyz4R7DvSWZw98kgRSVJYsCPgsbHugPn1FvIYNDOFGQBwXbYC2xObqHkBCh6ePYq3LM32C6VFliUcjtsWhIpSG9JJy+vPUbsgeZz263Jvf4l1lcM40K1n+bz5fHTDLWH5Dwk27vEXEr65uJIzuUmGDrOwt1//PAv6O4bf0b6+Iv5/dchO1+Iev+SxbFvWeDzWqpE3coso3LF4KT51U8mUrUfUb31ib5Zz8tPn7Wl1aMg+QvL8l/MNDdISsVzioxHXPyNB7sF6HshGEj58BmoZDhB4bOVj0g++xr9tzvVTDYTTdYzJwdqI0N9Nf4hhxEyG2tCMXtheXayLFuUy9+Z1yPCtiKzYAE3XuhBSWccmz4P2aKrr1HoIFVpsa+mLH9R6aURz7LZo8VZHWzQ345WpDSNQMBrC0PmBjQe8zXfIplqKip9Rmm7UWopgWx+O9tAZmGFB36ORTVXoNZTsQnxlt6NxzDbkn6/EpUXXWL55+AKHMXVzzwDq4/egVkoiFur/9BXrr4tw9LlCki6STaDCxlkwB2lLL2IP35LGq/SycZuU0EWLqtLY+B3v5EiKTdlWSRloF6NrMKm/Rl15xPvAHIQZN8k+q2O43PeTcAaXYJ9IKMq7fj1RqtGIZkJlV4ctl6rciWEkOxt7GNn7mIUbfRHcy8YwV7NBUpRx2uIZyXl1Y+M8PIXMruE79TChb9H80SgTs2OloxXs6Ui1Y6K7yEk8SXjtYehCaE+WCIlifJMqRgEPpdLJeWhTmIHasmlLHEwKjkJaYwzK1toz57pW67FrBKtDzCIkUVFYW+K8oPyIj1E/i2Yr/1bdtZOnWk3lJdPHQEbje91outWHcKyioTWi4QzN4ZiRQksNM8F6Q/1wd3hguoetOH/EtQgwNyEfy9JJMOKcXHts8iB0HEFrH+JGdxuaG3AqvmankTS0g5JvXxTL3KqwCGytPPAEZDLvzkkIfx7yeY6LHzTgnD2QkNpM4LtHf+JbFqYG9CzUGxoLYbWyiv0LoHGdG7O/ipL+mNkST/kqZhgl5b0zsAh9VnmYsvQip4gK3onzLaSPYaeIPQuo6HGPztXyy4fL4fK4+cSwvLxsqykuXs7/KspRPCM6Zo9Hg3v0OoCpxFsUG9NEqOpTGlBUZcFW4FrXx0Itq9ywGRYsM2cZ7fLyYDmNDdkzG/jrTAb/d5WGEOLLTEbFKvMsGtRbA6QoNku9XLzzolsmH/GGdUbCg/kGQ/hGq1y6koDSEvo3GLBBkgYrNdcCDSsIvsuLJMxOzsQbME+W+ylrXokblOHJBeAXw6zgnXTOj3Rv19AD29rQMHxIX9qsSttrLRdNq0rbRl6XUbg0CqXX2nDEm3sMfSkWSkRTLEmE2mD+ZSEuEdHBzHHfn73BahasKvIDr/duMUoc/KmLkg7xKcXZNqAGoIEOnYW4FIxKDmIPk/MuwCbwlfjOwXb4umaQB0gxujBKAbSnpmcIc26LrQvocm0nKNtN9MGIiikGqW9gPrf8JdNUzOBeMaG+MuQqt+JVP3OyUCI2eyJoUIWdKEll7/y3nngZ6DZk6PAiLiAtT3pO+WrmWksdvlnTysB0g+C5BxUB0ITQRiBbYGL7iRoDmRzJuorzthAWxhQhK4PaVlXXPxumAtstfCY6gKc2iOzpeeszXeqXmmZeBjDJ1phpCKneg+FTLTwX+vo8CV8rfNU/A2RbfpmpJsOJOmQ5EBziMRcgosRpGQkFoQv7qKicpsLSM0zCBMEFezmDpsMxHgsRVyaKUChHWBUbiFu2LsQdoE6oB54AxabPTGvNsRtn5wVeg1kwZz3oDiGIR5A+rPZkHlrR3oDTeog9HAX8x/d5IBliwutXWjAOFqBOwbjem18bWkvfw4aiQ2FFtny3FBxEeX6S7knOgHVPK0NJ/6Xn3WJIrEH9x/rLhE55ajBEba0WLDi/4AirJ4PASjW8SED+7T8af1Et5NMR0HClygxtIOBQ5FMQzsWGxkyWQOqun8RPQJoAhAABwARiLk=
*/