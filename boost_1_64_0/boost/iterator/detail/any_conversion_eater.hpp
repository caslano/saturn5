// Copyright David Abrahams 2003. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef ANY_CONVERSION_EATER_DWA20031117_HPP
# define ANY_CONVERSION_EATER_DWA20031117_HPP

namespace boost {
namespace iterators {
namespace detail {

// This type can be used in traits to "eat" up the one user-defined
// implicit conversion allowed.
struct any_conversion_eater
{
    template <class T>
    any_conversion_eater(T const&);
};

}}} // namespace boost::iterators::detail

#endif // ANY_CONVERSION_EATER_DWA20031117_HPP

/* any_conversion_eater.hpp
ZWtBpLLP2TfvQZ81gNykfA/0npQlzqQBvOcPTEw9jybOI635LoqvMeHkcQE1m5T8E4FWje+kEHz7F+38uj0xWBgkn97xt5Pfq9rwp1ggR67ji875VOJlT3t7EDJdYYycWXCgaJMatb6EZJV0gLb3SW2g3Z963vdQFpcL9kvxQRGnkjNTQ4s2kVmkWyOAi+VduPXIe4K8okUM9PHe2tQ4ka7BJfd0plsUFof2awxVaVRwLJ7eTYrlNpN3OWT72i4FNneCHFdwuvqHj68GgXRw0iOWQ4MqKtyYs73zGZlNTHFb0nFJ6gT5ojTxlPB74mzFCcXhQBzWpgBXZ+5Sk36MCJZ5xaxJqE1kI1yNmzEtOnXubGVy/Ds2oMIU/DgszRWJdQMtJkcZjDeDfGmpxeWGIlrd0h/ce/CDqv05t911EqxPHdQPpIV6Dkt6fre7EPtKiAYEGVdl06YwR92GJXRiDcTJCAd0/J7xjNKUWY3bLJVGGd3aoaM/HrAovmCXtwwOrnHjUQMWF+RzqgUEr9UQSQ04GekoMXRKM9j5+18Efc5MPeCm5wwPxGV7FQ==
*/