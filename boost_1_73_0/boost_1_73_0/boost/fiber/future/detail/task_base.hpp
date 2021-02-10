//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_TASK_BASE_H
#define BOOST_FIBERS_DETAIL_TASK_BASE_H

#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/future/detail/shared_state.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename R, typename ... Args >
struct task_base : public shared_state< R > {
    typedef intrusive_ptr< task_base >  ptr_type;

    virtual ~task_base() {
    }

    virtual void run( Args && ... args) = 0;

    virtual ptr_type reset() = 0;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_TASK_BASE_H

/* task_base.hpp
LKyEcMtibLD0Q9n5jVlNt4D2tD87n47gQzw877OpwKWC252i6s/H70AGqu7mE20NbVw9G4Pg+ejdaHwxmo/9FYeUkArBfCvp9yEeJmO8zr2ZfjVd6nloYSNhCfYE7132vi2yZ+V/UEsDBAoAAAAIAC1nSlJH7Vho9AQAAN4KAAA7AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9QUk9YWV9UTFMxM19DSVBIRVJTLjNVVAUAAbZIJGCtVV1v00gUffevuMo+bIsSp6WCBRbQmhCohRtHsQtEqmRN7DGeZeKxPGPaaNn/vmfGDqXQpTyQD489vvfcr3Pv+BcjuvfLPp5v4ejOT+b+GT5Y90rLVv3Nc3O7QpZ9pv4LxQusP2FqStdan7ND+imtz3TgtLLB1lN7n2U/Ye7COmkvU6t8kdlb7PSag/5MNbtWfKgMHcwO6fjx40c0oftHx4/H9JLVgktKDK83vP0wpqeF2/mrYldXvubPx8QNMenfAEwroUmr0lyylhPupch5rXlBTFPBdd6KDR5ETabiVArJaRYv1+Hi9ZguK5FXA85OdaQr1cmCKvaJU8tzLj71MA1rDakSCMAvhDbA7IxQtQ/znAxvt3qAsU4wqRWxT0xItoE5
*/