// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_USED_HANDLES_HPP_
#define BOOST_PROCESS_DETAIL_USED_HANDLES_HPP_

#include <type_traits>
#include <boost/fusion/include/filter_if.hpp>
#include <boost/fusion/include/for_each.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/handles.hpp>
#include <boost/process/detail/posix/asio_fwd.hpp>
#else
#include <boost/process/detail/windows/handles.hpp>
#include <boost/process/detail/windows/asio_fwd.hpp>
#endif

namespace boost { namespace process { namespace detail {

struct uses_handles
{
    //If you get an error here, you must add a `get_handles` function that returns a range or a single handle value
    void get_used_handles() const;
};

template<typename T>
struct does_use_handle: std::is_base_of<uses_handles, T> {};

template<typename T>
struct does_use_handle<T&> : std::is_base_of<uses_handles, T> {};

template<typename T>
struct does_use_handle<const T&> : std::is_base_of<uses_handles, T> {};

template<typename Char, typename Sequence>
class executor;

template<typename Func>
struct foreach_handle_invocator
{
    Func & func;
    foreach_handle_invocator(Func & func) : func(func) {}


    template<typename Range>
    void invoke(const Range & range) const
    {
        for (auto handle_ : range)
            func(handle_);

    }
    void invoke(::boost::process::detail::api::native_handle_type handle) const {func(handle);};

    template<typename T>
    void operator()(T & val) const {invoke(val.get_used_handles());}
};

template<typename Executor, typename Function>
void foreach_used_handle(Executor &exec, Function &&func)
{
    boost::fusion::for_each(boost::fusion::filter_if<does_use_handle<boost::mpl::_>>(exec.seq),
                            foreach_handle_invocator<Function>(func));
}

template<typename Executor>
std::vector<::boost::process::detail::api::native_handle_type>
        get_used_handles(Executor &exec)
{
    std::vector<::boost::process::detail::api::native_handle_type> res;
    foreach_used_handle(exec, [&](::boost::process::detail::api::native_handle_type handle){res.push_back(handle);});
    return res;
}



}}}

#endif /* BOOST_PROCESS_DETAIL_USED_HANDLES_HPP_ */

/* used_handles.hpp
UdJE6o4fRae879YCz8CkzAnDx03MVGXKi95volfSNwk9h722JF2qqL7ZnT7xJ2tk5kRRM8rEs1KfbNRD+K4x9sN5XmSbyefn9MP6X8W/ENz5UPxr5ltUIOxTGMfgO1Sl3dPyjL/BPlhTKK9l2Bt9pL7YlUOpDtWOuyvrT3jYeyvUo72KKV2gHoiP9tcDVb3ltf7em93h0R7xdyf5+rX4W8s3R+Jp7PlE1x77hI20zbmtvlHOG9Lv0vqptp3hdovIz7WlYU+GVxA3fcRlk7g5xPdinNlvrvYukk5bs75tssmv5zXr29vkejDPS1Vx6zDh2yFu9fWtVW4diDbSZeJEe1qnvi5zSLl2mW3GNfJ81zXjsEKuveyxFGY+Y6tEpvpCzGdqVGyk1pe6yZ6GJ0hTe7ynxX6u1Y2s5b3XVS/mCa1x7DUS5q7Ef6+EuZNvuYTZ2AsqPStnVOYEI8yx8JtX/XqD8L2O2B2D3YXi9sy4o7G605lmKm5Q6oseYi/VX2eLn1t8Sb6C4wx1VfrMkHge9ZTQBuiz9blaBVe0do1rlxbuHuEa7ymm3U7ZecRTXtsODT/mbZMyabblW24K1FEtKHu3azfpRhreqeqpupek4c+Rxbx52kPesXpC1GLtk6gKmq9YE21IseFa0ehaWsvoMq74S8rpN1H+8lmpQFo/GKXKGKXtsFaLzQXneEtoz/L8X3IenaqzhpImDnu2SXoN4F4fSa/XfSmkl8MZbGYZ7f6K1BfmflbPyPWDIZW1I+74kDwtCfdScO96cW+jb0b4B9qzEctd8bjrsB+c6e5DkkbJEtZzF2x7g1n9WBLWGrhdXdLgZFxH+/NkHwNB7yPc2Clh6OlbhZ497hOGZWfY/T4rcShq9jmGyrMdIu5k4F+GuLPBV0ziEPTuVXX+FPTGid4KX0hwGlJc7f49KXoHzW+LiO2Spmb/Q+qrVv9DHL/qy/1y6r5RBiLF32j8PSruNfEtJJ5Be+KZZfd6caOfVskYHxU7W2MG66e0ekV7aHOKvqhNLjZCO16squaLfkoPftaljWBep8Qd1+pFVvbGadd5u2nrvVn67VFFtOeiIrU3o553F4j7sDEjJ+ZOCPQPEVZ730Ito4/mRWmbhXrlFLxOWjacpv2izdAnawmube7PPcW10FDr3Vj6ZTnLjT6pO7QklWfnRZYY4pIWsDfEx6+oAu/J0+g6vLOttpP0j82TdJnn+8JeZmhHjM0ZwwZ1Vh4uFr2iZh/RbInDBBVGo023wHNRqxvid7svbi8XO7m+vbjtsC+hhKEtepXF7g9xXYPfyVkjpmqq374CerVF76u4AbEltbb2tqn1LWGmWV1JH2poCSN7TfJ8ZIn9tXER2A3aU0/yawc6Rp+utF3UnoQ+uGazlFnerI2ZdxDHSFQCu0gWoa89wxXmTnQb5a6H1LM+ax6Fer9UKlCWc6kbvd5a3tJaH28P7eWoEM0THa4NjZmiBZVDCfsZwnVQ0rKd7zHCbrU5xmakUd7M8x1VPfJ4oF+Q9Bs2xv6O/FDCkkTff+D9n+xv/4m7h3y1fbp9z0e535P7L8n9ob6Nyt/kZNU+CAyZadeoeHcVvdK+1TxfQ4pGaLN4xj4o+rLWj/p+YbHa2s5io7QG0dW1zOiHXKFxB7QjcU0JCXZtz9gJrYVqo1R02GPS6t/YInVnCYnzMRXnNtHW82eve+pL3VbJrL9HyvUB4nIfe/aUlniOIp4nJPx1fXcZ5cr6rjHTd3eBdjDtWhYwZo3LLtAOaSruzI+6XqscZbTtl271y8YyP8Bjls+cl5BxbuczWnuzHv6r5E+IFtT+DX6uJcxfEpbO4tc7vqrkncNelhLmUxcu2a8=
*/