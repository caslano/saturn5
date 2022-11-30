//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_WINDOWS_NAMED_SYNC_HPP
#define BOOST_INTERPROCESS_WINDOWS_NAMED_SYNC_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/detail/shared_dir_helpers.hpp>
#include <boost/interprocess/sync/windows/sync_utils.hpp>
#include <boost/interprocess/errors.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <string>
#include <boost/assert.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class windows_named_sync_interface
{
   public:
   virtual std::size_t get_data_size() const = 0;
   virtual const void *buffer_with_final_data_to_file() = 0;
   virtual const void *buffer_with_init_data_to_file() = 0;
   virtual void *buffer_to_store_init_data_from_file() = 0;
   virtual bool open(create_enum_t creation_type, const char *id_name) = 0;
   virtual bool open(create_enum_t creation_type, const wchar_t *id_name) = 0;
   virtual void close() = 0;
   virtual ~windows_named_sync_interface() = 0;
};

inline windows_named_sync_interface::~windows_named_sync_interface()
{}

class windows_named_sync
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   windows_named_sync(const windows_named_sync &);
   windows_named_sync &operator=(const windows_named_sync &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   windows_named_sync();
   template <class CharT>
   void open_or_create(create_enum_t creation_type, const CharT *name, const permissions &perm, windows_named_sync_interface &sync_interface);
   void close(windows_named_sync_interface &sync_interface);

   static bool remove(const char *name);
   static bool remove(const wchar_t *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   void *m_file_hnd;

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

inline windows_named_sync::windows_named_sync()
   : m_file_hnd(winapi::invalid_handle_value)
{}

inline void windows_named_sync::close(windows_named_sync_interface &sync_interface)
{
   const std::size_t buflen = sync_interface.get_data_size();
   winapi::interprocess_overlapped overlapped;
   if(winapi::lock_file_ex
      (m_file_hnd, winapi::lockfile_exclusive_lock, 0, 1, 0, &overlapped)){
      if(winapi::set_file_pointer(m_file_hnd, sizeof(sync_id::internal_type), 0, winapi::file_begin)){
         const void *buf = sync_interface.buffer_with_final_data_to_file();

         unsigned long written_or_read = 0;
         if(winapi::write_file(m_file_hnd, buf, buflen, &written_or_read, 0)){
            //...
         }
      }
   }
   sync_interface.close();
   //close_handle unlocks the lock
   if(m_file_hnd != winapi::invalid_handle_value){
      winapi::close_handle(m_file_hnd);
      m_file_hnd = winapi::invalid_handle_value;
   }
}

template <class CharT>
inline void windows_named_sync::open_or_create
   ( create_enum_t creation_type
   , const CharT *name
   , const permissions &perm
   , windows_named_sync_interface &sync_interface)
{
   std::basic_string<CharT> aux_str(name);
   m_file_hnd  = winapi::invalid_handle_value;
   //Use a file to emulate POSIX lifetime semantics. After this logic
   //we'll obtain the ID of the native handle to open in aux_str
   {
      create_shared_dir_cleaning_old_and_get_filepath(name, aux_str);
      //Create a file with required permissions.
      m_file_hnd = winapi::create_file
         ( aux_str.c_str()
         , winapi::generic_read | winapi::generic_write
         , creation_type == DoOpen ? winapi::open_existing :
               (creation_type == DoCreate ? winapi::create_new : winapi::open_always)
         , 0
         , (winapi::interprocess_security_attributes*)perm.get_permissions());

      //Obtain OS error in case something has failed
      error_info err;
      bool success = false;
      if(m_file_hnd != winapi::invalid_handle_value){
         //Now lock the file
         const std::size_t buflen = sync_interface.get_data_size();
         typedef __int64 unique_id_type;
         const std::size_t sizeof_file_info = sizeof(unique_id_type) + buflen;
         winapi::interprocess_overlapped overlapped;
         if(winapi::lock_file_ex
            (m_file_hnd, winapi::lockfile_exclusive_lock, 0, 1, 0, &overlapped)){
            __int64 filesize = 0;
            //Obtain the unique id to open the native semaphore.
            //If file size was created
            if(winapi::get_file_size(m_file_hnd, filesize)){
               unsigned long written_or_read = 0;
               unique_id_type unique_id_val;
               if(static_cast<std::size_t>(filesize) != sizeof_file_info){
                  winapi::set_end_of_file(m_file_hnd);
                  winapi::query_performance_counter(&unique_id_val);
                  const void *buf = sync_interface.buffer_with_init_data_to_file();
                  //Write unique ID in file. This ID will be used to calculate the semaphore name
                  if(winapi::write_file(m_file_hnd, &unique_id_val, sizeof(unique_id_val), &written_or_read, 0)  &&
                     written_or_read == sizeof(unique_id_val) &&
                     winapi::write_file(m_file_hnd, buf, buflen, &written_or_read, 0) &&
                     written_or_read == buflen ){
                     success = true;
                  }
                  winapi::get_file_size(m_file_hnd, filesize);
                  BOOST_ASSERT(std::size_t(filesize) == sizeof_file_info);
               }
               else{
                  void *buf = sync_interface.buffer_to_store_init_data_from_file();
                  if(winapi::read_file(m_file_hnd, &unique_id_val, sizeof(unique_id_val), &written_or_read, 0)  &&
                     written_or_read == sizeof(unique_id_val) &&
                     winapi::read_file(m_file_hnd, buf, buflen, &written_or_read, 0)  &&
                     written_or_read == buflen   ){
                     success = true;
                  }
               }
               if(success){
                  //Now create a global semaphore name based on the unique id
                  CharT unique_id_name[sizeof(unique_id_val)*2+1];
                  std::size_t name_suffix_length = sizeof(unique_id_name);
                  bytes_to_str(&unique_id_val, sizeof(unique_id_val), &unique_id_name[0], name_suffix_length);
                  success = sync_interface.open(creation_type, unique_id_name);
               }
            }

            //Obtain OS error in case something has failed
            if(!success)
               err = system_error_code();

            //If this fails we have no possible rollback so don't check the return
            if(!winapi::unlock_file_ex(m_file_hnd, 0, 1, 0, &overlapped)){
               err = system_error_code();
            }
         }
         else{
            //Obtain OS error in case something has failed
            err = system_error_code();
         }
      }
      else{
         err = system_error_code();
      }

      if(!success){
         if(m_file_hnd != winapi::invalid_handle_value){
            winapi::close_handle(m_file_hnd);
            m_file_hnd = winapi::invalid_handle_value;
         }
         //Throw as something went wrong
         throw interprocess_exception(err);
      }
   }
}

inline bool windows_named_sync::remove(const char *name)
{
   BOOST_TRY{
      //Make sure a temporary path is created for shared memory
      std::string semfile;
      ipcdetail::shared_filepath(name, semfile);
      return winapi::unlink_file(semfile.c_str());
   }
   BOOST_CATCH(...){
      return false;
   } BOOST_CATCH_END
}

inline bool windows_named_sync::remove(const wchar_t *name)
{
   BOOST_TRY{
      //Make sure a temporary path is created for shared memory
      std::wstring semfile;
      ipcdetail::shared_filepath(name, semfile);
      return winapi::unlink_file(semfile.c_str());
   }
   BOOST_CATCH(...){
      return false;
   } BOOST_CATCH_END
}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_WINDOWS_NAMED_SYNC_HPP

/* named_sync.hpp
5h+TW8VgkDZX3FYKcYzRCwGuFU9lWvdyFE/vlBrXmAlARZPCos37FFRr4fbE6qwF1DT6JP2vnAV3XT0sgjyxoLMcIXD/jqVhG24gdskuCd1fsrAk55rzZ7nh+SOPaiaCLabwWrdNzNEmqCFSEsHCdmFruMhspFNEamQYgdG4NMIdvX7PCkbnUdsV91wVlUvufPi/IozvGxx1teNbasidjYzptVjl6mM9PoUqjmaXSqCQLmMqRNYatEIU9cdYpFPPx7/ZFIoumNHPgckUu9ZL3+XYMJzKH/7aQjTLbm9U7ElC2+gceRHTW/Zjbe1cg7e0Zn02NrGAXr6ujt6KULGrBpD99S2K0jTEUHzQPl8qk9eJE4YlAlD3KC8nWK4VFulc2D1xup80jWxf+0FHey/IWIiCx3HCAa4CMOXJBLJplTu/g4aWUcusyFaHHKAoyU5qAw3pU5g7Y6ALCjxPk3Pbkd4fesHBxy/KvHEH39KcDj5KRZrMMh69KASoma/+EIEmkz3/J00rBNA0mdzKWzEx50yLganat+7c/zaiqv9VmU2uoMQqY0YugMKuKbVH+hzeHL5PPXYI1p+g/YznVoQf4dmLQV62GzCeO6GtiWyV5XVXmn/Z0w7EWhkyTeWVkE+Gh2jPxiWqjfQ6QxQgHOybS+S4/+VJUAXKuOhwQ/AASalzm1jQcPBj3lUQn3+qa3r2ht5H8+p5wWOL0GUs7QXPgWqIvILX4xXz+62ai8Sno+tecyOVxOByE28YMgIzMttFEQdNv032ZNelGt8jdGTYvHucXHf+ciuSmaYxM7FkEMoiNzsckCl1k+wRKXZuJulsjBwZlflLmMIguvwK4jV81af0FzRrREC8K5GapkxU0b7/V3c+To4yvdArKrbjYEMgXg029NF5Y/P+INw1p6BO3iHp4kaRi+7/oQXU7E2JLJDI/Y8IsLHV5k2e0JWp/vuXacOpDC+CWsPqG0f+FmFhuZNkCW+hpF1bpyyQDn2hVfflIFEru6idB0Xw0n9r7PUbt2IforPduOUjo3PzwtJfEvTL7klPcA4pkAP2dqWNLJS3ULFQUbM7UJK2JotU6kjF7bmflQQvVuJD/Yve9MRJ3/2rz/XIWJZbBXVEoty+v6QnsBGU2n/4IF3RYxxyY0QRlGAwIoWJHNl9dfe6I07Y84gYrpoKFRdAgs7geFUsg/XaMPnFVb++3msYIBTp6IIcZ2AQeHc9e1E+4jJb/yMfedxi5rfA8oG1Z2jIR/Sk6obX5ueEX9Xg178kWei/4GOVGr8bT6EcXDUY+LWPSW6Se6FQH1jWeRirsG8L2sCjsE4gK60CM2WZq1XQTZU/2JhaHI8tY4SJK5mSl3pDiK6kEjAa8aMjLymjhFaFotxUIru1Y12vKPg/qC/pN3OzA7MnNrMA3r6xGIfbIgdjBCYa0v0wKJJ20Vh7rV3BweX9An+IKbtza2+MLMHmDNHzxE9Wm4neNF6pZAfc5QMyx//9qasgf+BQZpTbibkKsdqIFRMAgtZUOnDMIO1Nnq3nQM+9vZSuJpbHiziSK3TdJWtzW3W+mTrKCQP9PO2eSQ1bM26AraeunG6q+Zs9myquS1TDJI021sSde/wGPGCw1LQppOxYQKj7xRpjYx2YdnL7CHa2GL5PU8uCHeMpFG7VQsv1XxV43pePI0bD/9zRuVqSOY8r21ZH1OfJDeaCgpeTLg4Ef/9m52CrXT34avOxaQGGYRGZVj2QLx6EUEXgyz8VM1xYs1vsuVcE13y6+woCHDT1LzXWa6EpMrAiWuXWERjkcUBFr4no0c7TWYAhAxiMG9/pI5gnJ7opWlfa4YmMjCQmhiyMV0oqeoV04bhBJ5XHxdXlTQsZ33IcejUCDIkLsWRxoybrGxNlvPlnGpHGqzDHdNMzTKGj53+wNBLkRyMGslHxSDjJk5rzJqvCwGaTaOwhjhHqZjkmbVt1Ap1KqNnFMZCbNf2Dfa/aj5qkPV0WPz/1gDGN1Sba3PB8f64ChfWVDT8P2QHH2UDcD2VCL1Pptkus7xUqXXCqCRuF4rU0IA0NFPsiEfDnPYlBLUjxhu/1nNj46Ugxl82589VZx4INTRdoccwZEv+3eNqjKdvXa42LQsKKjg/PkwrgEuMSHi/HGBqQ0Rqqm73PlO7oWetGgRBqcGCTI2gjrPzRjguFfTRYYkcVckgtLfzrQ4RYO0eOyO7W++2J5Zy+UT+RMtnXwOzcF5VKKFOrpeWSh67YzV9qBXc/9BDzyM9fAnSRFJBJlUawXb8DYjx8AyYxRxtZwUIV2tbdyguX8sDaBpxIIgcMoE3MvUYdktpFcAZNS6IxvxBPfMO72+l3caYAuezUEro3SdUtUJ8W7QZG+Y0rjI3DZbIN72CdpVkEPKxXRWcCjC3XMQCo0hX6HdnzXSqqVm2bRM3V8ZHHLv9+yrlwRNH3hPuXbCmTQ98xDiQGidDSiYEixtYZ4GJs9K5M1NfGVyz6ghmABtvYZrOKeaCfIr6XEOU+j1l0yDD5iLRD/FfnsQU/JSw4tUrR2TyZxvDWFlv5mIP3xqmr1wRo76NS2DIxcxRuNbuhVE4OXoQYrpcSaKZniWSfmPeTgqY8RE0B4FEt1AhexrUYzbYOWyXwpvoSk7a7wZnicwq/1oj2eE3+0a7MWuWB3miUna5NCRIxU0QWwc166sFbBCFX6YXbKaMj4O611tRskzw0Fm4J7heuHjplsJJqUSgwGQUW5IGcxWLbJWL6KY/7DpG5On3TWUHfV+VsZ5qIWBaRx6nK0USLuSwAKmtEqGxjNOGOLqaCrKYf9ObvwfbXgiDxCbT2F+7rovnIAbd/9+tZBIVE55EcuP2P+CmepGSF6QScCqJbAoKY4yVlf8U/72J4PWi1WG/4fdZbLnEp+qdUoPi89A8bnPPClG3qQkMcwn8pNK+ojxkzff37ZbYxCKqbizxReBcD/HejxAjw9KZ3kT2BxgmDERH3epG38P5lhyzl15VHdPNZqs0cfogoUABk1XC0b4OOwE+Sfp9h0ibn/U6UqE5qIR831B8ZulmkLtDq9B3e13cz571myJuWUzGiwpLBPY8RIWJ8VRMe4icQ2fMfvrtCszXYgraJuCMH/GG3kOFb1rD4ObdNDg3129/Tkk8DHsDuQwdGe9k1bPmGq6Xr55cew3WDcz7eEJhRT49tlLoSRY+w6xf3RBNRqoBUSmUDM6tHls2ffFqPFVV/F+GD/V+86lyuHohnV/Tj1fDfPlzmBnqiK6VCANXaU6K4sxQJg+oCb3Et8iJcHlkPbxHKIWTjxOazy7vWvTXJaroIXfQZoqlq69DTV6/rhwwSVTqR2mvP7k1x3+M5lx/lBsFfTdSYZcSj7DvIMRWXp1Qt+1YDSRqPuFAugVqWZBBFTKmiI3NfSD8kAAgs99MNMR0c9vcNml5iN1v8+TeceUWZ/kRVUxFVlPkALVpM6fDW2THClALlMbi2wcDH/yFuyc0GLa9nBW9bOXDs19ldfqxeA3fx+lz/xtfQ6BtJFcohZIxITh7dN5Pa8YVWTerxqvneR2l3wurdTxRZQDf0iUONbrSUrGkez292wDinzusZFbUE/cXLCyxhIi/8FvcH7jipNnRSkvZUgsZBfeMYwOFQGKi5xnSx168CL7InHohUNJm6v2Wy/eQQ/xsa1H7VS6LNTzTGgkKdm5t3Vs58qqMCycq0lCEVDi6L5UHlJPkdcq0ImWyobhVi45yXbE+SbZJMHzEdI6Ck6cwzMgm4zZOPDtF3fkLrZPZ62vZwt8poJKelO8UeEmRioOXIE2YDxHJEuU20Cf/1sIGwvuCY03jWXgPUa2u+yMJzMSQmZT2jBzSa8Eo/eQkeG/kgRgtZrv9Z2GQwtylYLLXdpqdfxfg53zqgCubTUQx+nwsYvvFnB4PJpH9fFBN9aey2NSAijUsG0Wak1WtfghMV+hgHAVnoCS0D4VPjEn/0tVcQY2GywTzokupWzYGESI81jU8qeF1JhyU9+hhc8kGtqWbhOdfOcmKf7CqhXjBlVAx16+YSBJGrykRjFAVXkFJkFz2q+6LOkWlqWHQMfGCLODVf0hVjbevdSFzxtmuW6UIBz2r0k9aLvkbtJAK47uWm1JkPhzXjQV3DyhQn4v6uGKpUxbjqXjty4NUs0+6nAwocCF3pcjgLQo6c2E3eYS1R14bbgmwyhSzo2yMl6b/69KDpcZlE5Lj99M5GKIm7oyXuneD/tz6Fx7scDsMJ83VjqDKNu74gMHPoKiEaT4AAAAACStVKYiJEgEC9bnDQ03qr5i8ugUUW6tCSI/BL1kgEWyqEHOsHKy6Lnewc1G9B9ve8lmX8r0Lxv8M+vE/ObFN9N/VZ5tsra7JcPRmU70l8ynF4DlQLB8vaRKK3fUtNfQVzZM6cCorJB5ZRjzf9mqN4B2FynzHvvsYKhCtKKlo5T3y8tjGPF7pTtw+TcwRJLJf+joIn0wNInPGysHMDAYFaKka1qgYnBz7ECejgDRxRsNZy0s3iZu4KMrKwtda6lUU4oEykYLiRt9EZCFEgDEQaLvRmkG4qyAwC3koSRH/ABiHT8wyGw6+0jzTdY3MobZAG4Ni2bdu2bdtOTmzbtm3rxLZt2zrh5t2t/XD9gZ6n++6qZ6YmQS6gE0VM4mfxod2P15Ge37dCuJf5XG32TRnFVplB1dPbQ6adccqczTuv/qwVelXKZ2TtHxFBEqVO9pkR7uh6SEku5nl9LnUVUGskNwqlSQTRHGpl4x/WEDDtLaADDjA3RUEpXBeiWsfkO+FxDUumI6+WJlJpZHKrZdOMKI95+3Knv4iqut6qscdh8M3d70JLmrSeuWcVqmnHGgqp0GMAboRYKjGtsSOCkICEw4dVAiUnlia46FQZ7zjxEpA4+DZtYiLUJBLFSpPtCjLleqkngQBxQX39g9RgjfRC5Z7TzwVs4oifvauOH736F5mPEOF/PF90W8yW33cPNrgoK2NxyzD6+YUVRw/qI22RbGOO66LAguqizhPpkpmf5Ys8PnsrvN5bSbAeeFffvvQPGmO/C8bRG+xymWfUICI2+k//xemPEBBXPQLUJWNGJib/uOvYJvkEJ2ymi2oTXLEQRGMAOAb2K61YOlXkFYyDAMQKPzuR8SJMT6NfeYAfeelNhwynanXGdz9cxcjZj3VsdaPBOPvDXOBbZBmJbhJkJsYpxglpScExo12RJdpYMIptpYo4DM3PRPyh2IK1cpDyqNvRY7Wi66RxvmuU2oFxAaQ1QfoHAADoDpgLxViq2wugGEaNtVKfFivu4OEgy+9mJiiNBXIh5CKRZoZboILOPfruwfSk+YPTPzBcs4qB/7yVYzf/5QW22V4EjSz7rQSLvr8OuxperNlD9qpGeAG4I1b9wx36HtTnh0+uBldSHHSuxFyhMj9vC2QUC0YAqJRwmXxAmE6xSpH8NHtDZbPIzYkr1o2NGto24uYwYIEkWC7b9LGyRkhD60j2TIQonyQ19fyR8DYXvQf63BQ6AxrDYOgDDZdpjuABBNRo/V0bAgF3tRwyuL6bvfART2UOcRICZEmm2IhKiqTPzlbLuX95mqxqlFBD+DSgCrTVFfytt4eWawkHWHGMFemPAjWriPHvpbiaD2YE8nuHhcrHN57o8xbsbc/HOBH0nunih3e3uYwhCjUZ/NEIwYFFm+kosdElnhptuenk8GOJBDUhxlO1mWiS7rnLCLpbVainVLUiqLmoXidg/gQ5FE22hx21YN18vEX9vIXUXtTaNgzF7AW9VOD3rOZMRIEyAw7KxCJqUk0qtWegjkSlRJIAABCkX798PxIiA4vg+BeZGmkMjQ8Hvo74pshs/7veBudc3LCiOb6CwK/YQ6w9en9dP8T7U/8s/MpLqunCyMq/s2aW0KIObJjdq9NIGsuPnlbisbCTmWcrWbve3I5aJyRBtYCSGZa9XauzKqqpoyMW0y94xlhoY95TMu2tsuCr9u50Q86HIoZE8gwmGTx05oiyYCDIEVx94F/fp7VEL39lqfpiMr2+30q0CJo4T1NoRt1SFIqOBECtTARkDuYfOU6ghzQ8MYwEAICguGtwQTsN7Bon7vCdmqViUt5ZTDI0KOAY9zPiB6qCpivPHYeX1wLVOEMTm0CeGgzgr0I87eo8AbUZ/Yr/3gkMNsY+V1ttpebj0bNeboJPiIHyZyF6gAkiUjvPmq4q9HHdZQDONF9xRZnhaK3YkJ8r279vVd5RNoUMnDvg8Zk0qK1Z4k+yvpS9sl4KS66zVGntUJsMsg8/MkcJwYLD/FJxnRdqaUiiJSpMkyWYNSijt3R7MyoH/IZ+JYdCcll0R6ecCaGxQaPnGEEy5dEgE1jy+NN2qSNlPMOO91dI8iO1aylraF7zyVY7OyCA0jCbeFX/0ufY1yQfTM4C76My6xc7tOhKNs4SlyLFbHK8OEQUoKYlgykDgt1BFE951QxVf4mjcE5xTrApr5dIonBQTv12FEIDhqdtLOcg6TipP3KzAktXm8FSYADskNIukLZVtUH1KxVy+UROZS1jJKW4oiQZfloyc3rH+8+Do76bC/S1NlfKATXv1PDnHdTNFaICTAbeb3cH/HY36/91N9yp8w1JIc6+6EdiZlZlZEFk+xZAvneu8DE7nbqllCwk5VzuigyaxhRVL3Uxxp+VNdt/vI8rXGhNlF966LMUErazmA+K59X23QtCBI2EG36aviSsAWl8O0JLiif2OUFr+tCWRCKOWzXWZdJcP2iFGMg7o21aW4CujXjC71BD0rPxfF5PvR8k7eePjXW8p1cF3A/RX3zIjur8MMoMC5SYtPVW6TrBVQsQWyIb6CNIPD5KLE8Dyev78DIzkbwovF/3OfTx8TETWaJ6RdFGQ0FhpFHBjpB2admcJFH3PWbX39fLi8VoxnDL6LCEiKx9PrctruRR96eAVXOnz1605QgYpoJVzGpZbBdw1X89htNKTBrWkdDNYQib8MXAeglXzJEFxpOGxYY4vawc1PFvXqr5NAJ8O+c9cO4UEt8Dh8q/coDLLCHKGFP6bapfiITLT7uNape4OoaT2bvBw1viDcshp7hT58Hy0ftecDpTYJuo6JtKdCdEYs9UlAnRk2lPgAIRAayOkaX2DbXLMSGKM6zrGUA235BYbRHraBKxv7dp6WLlSQqVFFcGB2LDwSDoHsbm3h/Ig3KnYGZgLv0yTnuRdjLxBfKDz+44/pWQjwv6bjXInW/uKMA2VwFvV18EUoIEuUHTEhXzdUhWclwZCNA6fZQOVG33UFsg2r8JiTauFhxjcrhImWfQ0ynXVCCXNrIZzWHH7JxvdIxgNU95dFYZFhtQo6N4iibbrKFtzvkrczZKNaRddA2kb0wex2rgg8mAzLxEtAumByJgNOOZUT1Nm6vuxgMA4om/7sodSaygHYZcws5y7F8sxs4EtyVy9jS04HhbpdQhq90FlSE5dH/AlGKmQ+oY2yMnCez7OD05+TYrMxp4EEVOvjc7Fty+RDiNKDJDyY7FoxCet1wvOaXTrl/BxtE6Q+jrTBBBsPZXquYRoquwHgcGAfabprn1p48VDEpm+gkkMJN7DZnLlzMwuUAz9pxbwV92gYQgSJeSmfmIFaLbyCCjkg2OKh9tTQkmcVKOBmVpPdOd
*/