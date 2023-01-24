
#ifndef BOOST_CONTRACT_DETAIL_INLINED_DETAIL_CHECKING_HPP_
#define BOOST_CONTRACT_DETAIL_INLINED_DETAIL_CHECKING_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// IMPORTANT: Do NOT use config macros BOOST_CONTRACT_... in this file so lib
// .cpp does not need recompiling if config changes (recompile only user code).

#include <boost/contract/detail/checking.hpp>
#include <boost/contract/detail/declspec.hpp>
#include <boost/thread/lock_guard.hpp>

namespace boost { namespace contract { namespace detail {

BOOST_CONTRACT_DETAIL_DECLINLINE
void checking::init_unlocked() { flag::ref() = true; }

BOOST_CONTRACT_DETAIL_DECLINLINE
void checking::init_locked() {
    boost::lock_guard<boost::mutex> lock(mutex::ref());
    init_unlocked();
}

BOOST_CONTRACT_DETAIL_DECLINLINE
void checking::done_unlocked() { flag::ref() = false; }

BOOST_CONTRACT_DETAIL_DECLINLINE
void checking::done_locked() {
    boost::lock_guard<boost::mutex> lock(mutex::ref());
    done_unlocked();
}

BOOST_CONTRACT_DETAIL_DECLINLINE
bool checking::already_unlocked() { return flag::ref(); }
    
BOOST_CONTRACT_DETAIL_DECLINLINE
bool checking::already_locked() {
    boost::lock_guard<boost::mutex> lock(mutex::ref());
    return already_unlocked();
}

} } } // namespace

#endif


/* checking.hpp
og8onPGAMydcgImJCff+/m/fvf6RzLefn4cH62ElgRAWKves/Fv+QmKt8BVzc3MwNTUF09PTMDMzAx8/foT5+flv+z2cCHDbfgNm9Tz3r/ivDJ0chrdo7YikgimvnQv/Df5/t1/9b/L/3MXAt9zKMziXzTfT6MZz7b/B/9ueD63FP+DLfu+/yf+/Jd/z/xX5T/mjuOVAcRuI4jYWxa3i/2v8UdzeQnH7AMXtAxS3if+v8UdxewPF7QMUtw9Q3Ib8t/ifkWv/r/NHvsKEfMUU+Yo18hX8e3IUt1tR3FqhuPVBccv+n/LH8cZBWaPzl/iLC3t8w1f+iCct4qmAeKognhxfn418xQz5igfyFQ/kK3b/Kdc/44/jrmfSB6panX8KsdNtwCv4DBRkbn3DV/6IpyLiqYt46iKe6l+fjXxFFfmKB/IVD+Qrv/ye9p/Ir3D/nr+Gatw3YFbfVVIjnicRT13EUxfxVPr6bOQrVMhXlJGvGCJf2fs/wR/H/T/gT/2FJwXiKYZ4nkU8//Zv0X8kgFZggk+o7Mfgv8mDLzHflRVfSuyXEvMXJcG/KLHflUi+dIfB/m+WRIjPMgZDNoUvCeDPSvhSVv9xuXBi9Tk0jn9YEtLB6peR6DGrX6L69j2tv9zB/rGEXlXjCTS5gL1poFDhdknmvaOG5PsbKicrLJREsKbyx3n++RN/XaKttPRumym/DDI/DUaXT8It
*/