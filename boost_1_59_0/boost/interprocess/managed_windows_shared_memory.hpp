//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MANAGED_WINDOWS_SHARED_MEMORY_HPP
#define BOOST_INTERPROCESS_MANAGED_WINDOWS_SHARED_MEMORY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/detail/managed_memory_impl.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/move/utility_core.hpp>
//These includes needed to fulfill default template parameters of
//predeclarations in interprocess_fwd.hpp
#include <boost/interprocess/mem_algo/rbtree_best_fit.hpp>
#include <boost/interprocess/sync/mutex_family.hpp>
#include <boost/interprocess/indexes/iset_index.hpp>

namespace boost {
namespace interprocess {

namespace ipcdetail {

template
      <
         class CharType,
         class AllocationAlgorithm,
         template<class IndexConfig> class IndexType
      >
struct wshmem_open_or_create
{
   static const std::size_t segment_manager_alignment = boost::move_detail::alignment_of
         < segment_manager
               < CharType
               , AllocationAlgorithm
               , IndexType>
         >::value;
   static const std::size_t final_segment_manager_alignment
      = segment_manager_alignment > AllocationAlgorithm::Alignment
      ? segment_manager_alignment : AllocationAlgorithm::Alignment;

   typedef  ipcdetail::managed_open_or_create_impl
      < windows_shared_memory
      , final_segment_manager_alignment
      , false
      , false> type;
};


}  //namespace ipcdetail {

//!A basic managed windows shared memory creation class. Initializes the
//!shared memory segment. Inherits all basic functionality from
//!basic_managed_memory_impl<CharType, AllocationAlgorithm, IndexType>
//!Unlike basic_managed_shared_memory, it has
//!no kernel persistence and the shared memory is destroyed
//!when all processes destroy all their windows_shared_memory
//!objects and mapped regions for the same shared memory
//!or the processes end/crash.
//!
//!Warning: basic_managed_windows_shared_memory and
//!basic_managed_shared_memory can't communicate between them.
template
      <
         class CharType,
         class AllocationAlgorithm,
         template<class IndexConfig> class IndexType
      >
class basic_managed_windows_shared_memory
   : public ipcdetail::basic_managed_memory_impl
      < CharType, AllocationAlgorithm, IndexType
      , ipcdetail::wshmem_open_or_create
         <CharType, AllocationAlgorithm, IndexType>::type::ManagedOpenOrCreateUserOffset>
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef ipcdetail::basic_managed_memory_impl
      < CharType, AllocationAlgorithm, IndexType
      , ipcdetail::wshmem_open_or_create
         <CharType, AllocationAlgorithm, IndexType>::type::ManagedOpenOrCreateUserOffset>   base_t;
   typedef ipcdetail::create_open_func<base_t>        create_open_func_t;

   basic_managed_windows_shared_memory *get_this_pointer()
   {  return this;   }

   private:
   typedef typename base_t::char_ptr_holder_t   char_ptr_holder_t;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(basic_managed_windows_shared_memory)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public: //functions
   typedef typename base_t::size_type              size_type;

   //!Default constructor. Does nothing.
   //!Useful in combination with move semantics
   basic_managed_windows_shared_memory() BOOST_NOEXCEPT
   {}

   //!Creates shared memory and creates and places the segment manager.
   //!This can throw.
   basic_managed_windows_shared_memory
      (create_only_t, const char *name,
     size_type size, const void *addr = 0, const permissions &perm = permissions())
      : m_wshm(create_only, name, size, read_write, addr,
                create_open_func_t(get_this_pointer(), ipcdetail::DoCreate), perm)
   {}

   //!Creates shared memory and creates and places the segment manager if
   //!segment was not created. If segment was created it connects to the
   //!segment.
   //!This can throw.
   basic_managed_windows_shared_memory
      (open_or_create_t,
      const char *name, size_type size,
      const void *addr = 0,
      const permissions &perm = permissions())
      : m_wshm(open_or_create, name, size, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpenOrCreate), perm)
   {}

   //!Connects to a created shared memory and its segment manager.
   //!This can throw.
   basic_managed_windows_shared_memory
      (open_only_t, const char* name, const void *addr = 0)
      : m_wshm(open_only, name, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Connects to a created shared memory and its segment manager
   //!in copy_on_write mode.
   //!This can throw.
   basic_managed_windows_shared_memory
      (open_copy_on_write_t, const char* name, const void *addr = 0)
      : m_wshm(open_only, name, copy_on_write, addr,
                create_open_func_t(get_this_pointer(), ipcdetail::DoOpen))
   {}

   //!Connects to a created shared memory and its segment manager
   //!in read-only mode.
   //!This can throw.
   basic_managed_windows_shared_memory
      (open_read_only_t, const char* name, const void *addr = 0)
      : base_t()
      , m_wshm(open_only, name, read_only, addr,
                create_open_func_t(get_this_pointer(), ipcdetail::DoOpen))
   {}

   //!Creates shared memory and creates and places the segment manager if
   //!segment was not created. If segment was created it connects to the
   //!segment.
   //!This can throw.
   basic_managed_windows_shared_memory
      (open_or_create_t,
      const wchar_t *name, size_type size,
      const void *addr = 0,
      const permissions &perm = permissions())
      : m_wshm(open_or_create, name, size, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpenOrCreate), perm)
   {}

   //!Connects to a created shared memory and its segment manager.
   //!This can throw.
   basic_managed_windows_shared_memory
      (open_only_t, const wchar_t* name, const void *addr = 0)
      : m_wshm(open_only, name, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Connects to a created shared memory and its segment manager
   //!in copy_on_write mode.
   //!This can throw.
   basic_managed_windows_shared_memory
      (open_copy_on_write_t, const wchar_t* name, const void *addr = 0)
      : m_wshm(open_only, name, copy_on_write, addr,
                create_open_func_t(get_this_pointer(), ipcdetail::DoOpen))
   {}

   //!Connects to a created shared memory and its segment manager
   //!in read-only mode.
   //!This can throw.
   basic_managed_windows_shared_memory
      (open_read_only_t, const wchar_t* name, const void *addr = 0)
      : base_t()
      , m_wshm(open_only, name, read_only, addr,
                create_open_func_t(get_this_pointer(), ipcdetail::DoOpen))
   {}

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   basic_managed_windows_shared_memory
      (BOOST_RV_REF(basic_managed_windows_shared_memory) moved) BOOST_NOEXCEPT
   {  this->swap(moved);   }

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   basic_managed_windows_shared_memory &operator=(BOOST_RV_REF(basic_managed_windows_shared_memory) moved) BOOST_NOEXCEPT
   {
      basic_managed_windows_shared_memory tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. All mapped regions are still valid after
   //!destruction. When all mapped regions and basic_managed_windows_shared_memory
   //!objects referring the shared memory are destroyed, the
   //!operating system will destroy the shared memory.
   ~basic_managed_windows_shared_memory()
   {}

   //!Swaps the ownership of the managed mapped memories managed by *this and other.
   //!Never throws.
   void swap(basic_managed_windows_shared_memory &other) BOOST_NOEXCEPT
   {
      base_t::swap(other);
      m_wshm.swap(other.m_wshm);
   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Tries to find a previous named allocation address. Returns a memory
   //!buffer and the object count. If not found returned pointer is 0.
   //!Never throws.
   template <class T>
   std::pair<T*, size_type> find  (char_ptr_holder_t name)
   {
      if(m_wshm.get_mapped_region().get_mode() == read_only){
         return base_t::template find_no_lock<T>(name);
      }
      else{
         return base_t::template find<T>(name);
      }
   }

   private:
   typename ipcdetail::wshmem_open_or_create
      <CharType, AllocationAlgorithm, IndexType>::type m_wshm;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!Typedef for a default basic_managed_windows_shared_memory
//!of narrow characters
typedef basic_managed_windows_shared_memory
   <char
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
managed_windows_shared_memory;

//!Typedef for a default basic_managed_windows_shared_memory
//!of wide characters
typedef basic_managed_windows_shared_memory
   <wchar_t
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
wmanaged_windows_shared_memory;

#endif   //#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED


}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_MANAGED_WINDOWS_SHARED_MEMORY_HPP

/* managed_windows_shared_memory.hpp
VRb7bAYJqACDhlgRIsYNFQtfcE/Oq+T7jcil1BLtKIZQGDS3gSnFfV6fCTF53vp0tZvdoPm2m06tuF3F2/2UmJyGZobeaajbOhjsapnZkA/n8tt2pyV3o3uy9WrTKYfrJtvZFpF9Fa0XLGyL+dqLPX+kAxRRUXcXbQca9bc9PcNuJT97BYzTnXwumq2Sqzcipn2Qe0I76Gtz5Pc8hUVQY+p9/9ch8j2JN+tLBPkRR7oZIhnlwy2/nTp2WfUiXZKgZlFNKFFt470WBsU+47rM1OLE+dLTsyd99gmi6+laAJDHaR5xJ2dq0iyFgTrdZcrU1Gvw3YwZxgTulRcoklHGkBUvvjFj6/81v8p5e1Xhs+VrALQhd2PibMvul6Mw/Ax+WH+7LnJuaP+QwOBz49+dUPYQzIEUb9z8ADu/rXuZhnNHk3gbWOtXKstH7SfdQ+z+RJjtyeVIqCcbuXvyKd6bF7FIblTl8rfroRiSVL6LI0ikH3c7Orn/714o6+ONxC0vAwf4xvJU6wlZwUHYyk9u+0x6FfsMc5mrNhPq5+PfLblTSc42jx2rOHdqF83E1ouQzVCDOVBO1Ti0aZfDQB/4haNlkxd4rFlZdaUGthzp8tdoDb71YEmAI4f1wgaphRzsSCrg5QL5RpxDufdzbfPTlrUHdVzqvJTIo9/VfuSG55tPTan9JMR+ZAKaNbiln50wPU2ehvD+2p9hPMeRIE1xnBgveVpqpdhtHokyJEtyefcXvf9DAlV6kj5wDvV3oJ9XpieOBFBQFt57p+AKqp139juUXg5aftJJ9ONJufct7B3TCBv3ju7Vv2GY9UCeeNbaxjXkXjMAwG/eTETKs6UFjdT6RP5mjxW/tZxLm6izUb3b7Mzd4bO1Z5uUuT5xnvxc4RVzewRylpDwIk0KDtOjpFfUPIsp9Zr4T+PRfNiwjEMxi1rtn2Uf1GM+MEt+TvWf1QTYIeO9jEc5bsGt1B/AL5k8rHOhiio2tY3KvXPopjwyy2Y1fatyl5IYy7UnJU80n0A+6bi5G2XRVjSWmz9Grcgm1mzz6ZyTjqa0DeVrc5MQbInV52pglaxXnrDGZ193W6A19NXZeG6dSbpDNVBQg5V9lFk0iOKN1LNAecmjI//vlU2+1+Oma7qXNK85hJdQz4M9T3avj07zmu89YKJSFsZ/JPnxs4iXbDq73O1pmFTNvwrChO/00ID/KUtpFoMmgFt3kPMGTe/hEfY5QqfZ5H8KypWpKJ0Hrg0LntCoW5bH7PqHlqMuap6jnGYZa4llCZIyaFPTUjbayumuTJwumVduon3lTDP/cok+FjPbfNcxJVSGHGft5d+BmMtZH7dMHqZkCfyQF0VzwDFTwKFjCOT9a6cp18Gwaaf5wWgyUP/rKJK7HTVUo+fQ2yWhQ9CW74XD8At9yNMyzu3iKqzGY+pCX0jpno8ypKqfjxAb9qXtVlCCogSFtQ7A0Z+L1knyHB8qibr72SLxUXwQ/jDtqO8R0Sm4TZ37j3sOOM0N6k5HwbYN/C5/1psoxlhC6OKpe3PjzYzfobBIE9MkntSAkeux4GHcHvgST8+c7FrEuMe9wzdegiqMazHVpq6iVaOwmubavyitf2vkZgjJxuLQH/qesgVrnDg9dJQpzVIesNhtFNrM7fe5/asH8lLkNdZ14OuICnbls0V40Jm+DXLT6DblJdJ1IQnGtMcz3A9F95+r8ENuIWK8wKAgr0Mth14WwpN+RDvJe/xHOjGtME3RP+aJGh3Rb4RYhrb+DxKZ4iwlYYu8RiWiJOVxNANBKY5+UHv+1EXuc/LdXwC0o6BtHKhH/t2ZlNil0gu4p613xa8sX12/X0MY+qZ50I16yj1wVPA5bpTKq8lPRsT2dHFrOMcHAUyLhM9DiIHcdMfmBoFt07AnNI03qAx7uG7pHQHvodftfn3I4Iqm5qEtgxu/viZOwhITkMzJGjE8YRIjYNiFvu4vFdD8XiR+39aW/ScEjfyc6AmqDoqT1HU7rp7k20qcCI2HND82ODQQseCnpLxru9vW0964wGWdnS9XYac2DyRgDZmxRXEn1u9K8izL+Ngnjf8nRiHj8iB1G9YZdwo2y9SVJv2pywPW6E7si5ooiUWC8G4X3Yj16a7VToYQjJhDBUh0G++ZMDvEzIJRFkqqGRcwoVFYUJooZ11ETBLEK732F4YPRn/OHzbbHyVqh72sqgoLIi18Sn1X521DNr5kjMU+iS5dFI3vX5wEMQ1um9uEysU1em4R00qsZlX5y2UypEnHIoTEFixr4JRmpF5rtZF91f0M7VWAJ9pSWK+8Y3Hl7MaUiH6Y/CBmi8Oe9T6+3YtTLLR4GYbRetp1y6dU0+vGjgJTHmJAiCJ3l2Sv6k7RiW4aGbULzaG//R9BH6VTLoe2Fgg4J0VTAqev/aYOrd3Ql8J/8haljyWWhVVclqLzkp+2IkryCDcFNCXp6zZXjLiClryV09wUQmWAYzeRcVqDMREjdB5kAKE+k+0Ac2r+Wxzy8X+vg/NqaNSL57YIjWIDzOKafsKsRyakAYXJZakM+V9wFqIjiE0Y65VXUc+6p0Pyz6BmxQ0QsbsZD70ee+DtTVtks8MLW0PXni3orczwNQaB7HDx9UGOkMCdrdkQRyHafEpCC3RFFLy6Ag2c94CXhG/K7v96IseKn+blztzOmh9FPKl9EgMPSxy9PDL4MzeDvedFTJrrZTSR+Kag0RQFqyube9uM/R2pypLnKix6QNQHDsbywBOlNSysmRGFZR9/uUaTXa6afMd29C05+TBYuVkxyBViLvRRympwb8ZBu0Zs/ZW8knkG3MJhXGnvom87paFtFiji/y11Wmzb3XQI7UDd1LxGP+fqOB1u/5Qh83roWvoUKXmtbcyf1TqFLWVR1qCpCnD7piMp5bJWrQMpCDZT8ygurlJBGO1LPjQyrwB3xPaI6pTnowNKZpvBBOBWJ9ENVmcmg0lJn1enl9ApqJdr9wIs/ItNGrG1jKp5r8XReeldNBbnMv+oIZ6SOxDxP6qIsW3GHQyLHoTczUkYl7AFTeUcGzgVt03xWOewes1+7eoOd1Tt5Fff16FU8d02cuNM3q8PWePNzQ/amr34r7ca79QlcnVbH4iepDysSp6WQA4chqxjXsYOReAGV7ZeIxbQ9HvapbqBr2NbGtXR6xn3FXsk/e0nEUSxqQtcVbqEH8ZDrO7jtq2X6F6fyJ13OgtKEvwWpSORnsXuFAJ2eMt1kwJJ5Yuix313T0mPmlFKk1QrD2TEKpSXQiyxqqk0WsLYoDm4EDonOuLgziP1sN3HvWQTsD1i9kP/JjEKxYQYYOT89bL1ZkLfZWlO80tbmYQ6hvtDuaI3EPCn81gh5s53UDBJWqPXtVeerIV0I2jd1sBvwMLY3j2kvUoZYd0oqGHjDbUm4SLu6XauR1n+WDtD/zBa2mc0M2Fer9jvQvhYsxmzrnkR3JtJVyvavZyUPWHg8O89+Ospae8MUEUHTVXP7kzamwmHPdBM+dlipEl9nX285qrYep6ZV07+F+Lc/lTVHX60H4A9ZO3j8mB3wa6I/YVrJOthmpl8WnL3HoY6h3+Pq7LMzP2oa72z33n0hNK9hlfjd36tcC/WyR6pT7SiCg+5HgZBJP/gf0qmlC0947/1w2SxmrDLqbetdLUqQX1PaxAWxayU9/ITT88eid81z+lOdJ96cMyiKxcVkycnf7liWsiJfRIERbVbxdaSCSnaNCFqkFdLG0DlsGdOozc8WSNZRWZuL+QYz9SlLnDjc2YZUFQMy3mRb44hYqjOHyU3HdtCsaOM39dlTn8MUe+fbcvq+z157PDKS+YUlP2Weitw6qfdoyeUS6Omw2CPLB2k3ue9K8f0CyOcIVlRyaDAS+KTQkw+kawoy+/ti90NzbSsGvcx/iu7YGuO1JT6WuqRS7jzySEfd88snMW3omFrzSKnSAC5842ZWziOpPca00SYMikOdMfroNRRledOsGfIfoB7UttyxucE5FF5tPgosi/qHtYENHeedPubapxW3zd7mnVdtJ74eYG8JCht0yiUUS1ihMKi5uepwapSZPIJRP8ujXzIq1uQWgsIYHXY4JawOKxy5Dsdk3LUrRXiUHFt/FT6hjXBKrpUjKU6SSod9yIVkM23TBLvqtpWB4bqaYhgFTpxRIlzRP3p+nlFKyzquvV2CtlJSTnH0oIadnGkrRsC16ZwjWODcozVPCrJnI1bWeGxuefbrXibmOp5kmTbhPGJY7KnppHooOtW1rivvJ7hPpiJfKsbtjiDE3fxoPV741h3q8R3v+l7NVVefB+0PIK66hQS4Hw+X6kol1YToL9CFPtN9uiyXEzNRxNuMVqGyA2JxgmPBr52EOy+hN5pSEMA2xCdH8K+RD3JPRNjefjq1BufPiMRMB8vym57O+firBra+TbzNVZ1Ah2/fNq6QbjemY4Wds4EDysK8xGuQb5KMx526REzzcy3//yGZo+nqjip3lhmOG84SoQcWYNAH3H3O0P/yPMZ7rZFchTjXsh6mqY7gVYRzFJG1N/EQOZHAPpqArC7W8l97py96Wf+kBZmOeQpoDDqwzDeYiHnqtEQVRhSvkbY37W9Ck6CPTcUwdondQLooHCLKRrcrS4FF0OOKil5FTwWZ1ZcLXus/Ga1qVgfQ9+hfSK7BfQL1dl9g1rwZdIfQux/b6qzsW0k0lFJPC2+q2gfoKZ2AskIUNMGqBp61sRTRqch9Mt71UPWH/IQZ94uKpwshoO9qHLE4RwzQUC8I83jJh4oeLskkyTXf/0kIYQEZETj374g50vIGXDZIY+GiIwaNAjfACS/LWRke2RgD32pkk77n60kwz5g+SHNPcBR0X67Z2VFaFSfQAmoYFcWt3RnDx9lsb0f6IpKrghB0ftxffwLhgrHJcY0STHDcHKI93WGRliLOjN5575qXI23Mh1NEFVMUpPs9RLlkqgDgmDIKUIzAJjBO4hvZteEtOa3yn7ZN41pxsW4peherlFaZNVWvWl7/cctSxv0VH/Z6rzpxXNPTMTTzaPUIce4CIkZ1iN4P1AUq6lFCJsxM02fhjA0PHGobR/59Gijd1BydnwiL+SVZRjv9crREYHiWLEIaUJJt7qUCbPmbztKsbdqAigaXlO9Vm6F1FljQa8wAf1gqridZaO4Cg3TMlZHDJmpdgOU6mpKfEs044M2afXOT41AsgofIleEVwtjNbnSlC8bYL6kgutNv60pWnhG2wW56ZK7ObQXyoKZphkv2PEnw76ZHpxalU4fzrT984Rbddfs5dZptskLPUYxkiaiQWuNhthr9kDXJR9Ihj8S8woKTNIch7PzwWcnirUV+W07ALIZxn6PxJmcgLAe9oLVmffxD1uDQym76loprhxjqeMc2qaATXsD1myqIdoBO1eQA9rFWzduaYQQH72PHY95esHUQU8cy0KOFSPDago7yQbbMKbBVCuqyjxKHd2j5YmELc6DDVB511ao+HyY65z1oBm9cM36guytXNSyqh3l3rq7VaAXZOzLh0kRjc4G8zHGjPBbPEK5bOWQ4WryTdaSVPbWLXMlVXs0+3Du9QVjlPoIL8mG6jyXNwoMqUglSFWxCRnpr0EQ3uv7yTl56wirCv+u9S0sIpMCIG9lGerU6DH9XYk3+F22P+bvMLin5sEON13/fnb/PrNb6WXls/BHE++C5mEVIe/gGiP0NiM83fqK09ys1ZUL6VULppu/ZRWrD9APnRCgIPoqa078+DtwkGdWuBO1hXFTKdgddLO3S+m3+x5H7R76or0QZ9NkC+8t/AfqG+80UXV9svMt2JHdEeq1kH0nNNYO5SG7dEZPus1vOOHduEjtUNURS8umFs9ANDuNuCoWGqgD3baVNbA8Y0eOok0BSc5t/KKWWPhg7ytft5W3+5gpHyA/gJb9d39wziz4G+WATuo7ilcfGMk/JckKFbEKQlZI6tvLhF9q0PFWQgi314s3jlKklUoCnDBXflA7WRqylaYDQH5Uz93qd13aMkoB//PwD4CWUishn52CGFJh7CDUO/XrwH8KIDwT3iOvE+5m3uyBB2M4gxo839qvzFND1nradjLZ5WB98DNXSK745n4T5b/wPrdh8sYjT5nYB7NBTB9ddDudS73g8qJi/9EVZINtJShuc/5rdx6BaQg+6jfNx8/uozgX1ATRTcKqmtXFPp3BzYpvH/sKCIo6agoPEnas0pGZSz6WMivuYdKirKiwpBzvdFWHKlM8Z2dNJ7Ok+3fLfs4tCcAo7LRSzRrk8in1lffL9wvF0LKyZkfEYo/ROGCdEndj+kiLCgjqlG4hfsqbKuz26ibMWtFcr9u25sicND7ntTBxq/tYI7ZHubkkcCUUdxkXoOxx6eYc2/S2hVlxniBCdP9mjUjtm7hCe5j2Yndvdii7+XbS/w0uN2tOdlXym7oIzakfzGIfoTUw9RD2XkK0SMGix1nIk9YnVUmI4LrQc8CpP1BlVtQoGSs8QHlc9SifKTSLMVeCC87lv0pHvtsnS3Fz0V1QXnNwvtQl/bhZm8LAuSlMESeoI4qLTTg3vyzOgc2/dMXqWvgagCq7ZezmGLyic5SbNtii7wk3V1ByBAUgOM+tzQnxVKbxUM+0Wa3vy8yGTBEddY5d9+HWc8/L+YIooRAtRd9cP/zfCAW9KkK2/7yihIfu9mUYYfW/0vVG7IvG53fmxSnjs6TpaKhnB/MX/zpIdpP3/OOf+PSZqh7XPOLqfrcjVaiO8Ns58V+pYG2E1LKygT5SxxBEKwqEoylWH2hpWVKeZyFiForWCgdCH+C6955ARCmI94E9dKRvjhsfBeIcagbILvsO9qla/XpCqwr54JUBBA6uOI2gOUiuuFIHIPApD7eFl3oWd453ins5MK1L3+XG5tWsqljTx5Lg1eKy91Tp6F4Tx/0kBLgjKinezXsQqWCmZDKGt8EtF2DSmWd/88Y66um2nZZ9Z1ufsZqYgScp9aKlSXEhndG0HU8ufsBNxF9+DSqKL4M/XLlk79bkDvOca3ufr+pv7TeF2Yi29G7h3KlkNM/+G8oemp8PLDZ7Z4lvPgS5xaagwDgcGOR+LAYd/zStSTp08A6HnReISPquJDDLXLffeCATOyk5UonmBae/LLq5HbOsqdGSbH3jZhbvX/24+98QlUeCjtxPmi5zGT7kUIdJnZXpS9XFne1WkM7Ko2nEKAsz5mbNrYpYmDM9zNur0Fv5aLY1B0yswV6vCL2muhuKD93o1lsCLux6n1mzQqehzSIbfvGob30heMaZeZm2wvXZ628V5exyvvpdfJyPhHlz5IpIQEFNmllV9L48RPaLE0akCU4iNL2Euct6U/tCDZgkseRtmlugFmS5oSL8GpclTOKmyf0ek7SfWlGwEtZ9rWy80gLLoN1XHRJ9P8+V0eVj0k9f632qVx33lEifk6Fhp+5P+plmc11/n/lbuhBuijDSEX+N4lbdY1QQgAFJz5Dk2kJa+Cnum1FbIa3s2hUssRd/K1X2ZzkUCj8oTZ8qtPeLLaG/fP4/mK3S8eLD590OZA4oUYdkKRb9JX2siI/cf496mllCqKwBKUpwBVzKENUp6DV4C9NWPB8jH1IjFw1P92IImyDbggzbaTBXufPwTLwNVP/o
*/