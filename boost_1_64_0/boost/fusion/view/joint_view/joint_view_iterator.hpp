/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_JOINT_VIEW_ITERATOR_07162005_0140)
#define FUSION_JOINT_VIEW_ITERATOR_07162005_0140

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/mpl/convert_iterator.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/fusion/view/joint_view/detail/deref_impl.hpp>
#include <boost/fusion/view/joint_view/detail/next_impl.hpp>
#include <boost/fusion/view/joint_view/detail/value_of_impl.hpp>
#include <boost/fusion/view/joint_view/detail/deref_data_impl.hpp>
#include <boost/fusion/view/joint_view/detail/value_of_data_impl.hpp>
#include <boost/fusion/view/joint_view/detail/key_of_impl.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;
    struct forward_traversal_tag;

    template <typename Category, typename First, typename Last, typename Concat>
    struct joint_view_iterator
        : iterator_base<joint_view_iterator<Category, First, Last, Concat> >
    {
        typedef convert_iterator<First> first_converter;
        typedef convert_iterator<Last> last_converter;
        typedef convert_iterator<Concat> concat_converter;

        typedef typename first_converter::type first_type;
        typedef typename last_converter::type last_type;
        typedef typename concat_converter::type concat_type;

        typedef joint_view_iterator_tag fusion_tag;
        typedef Category category;
        BOOST_STATIC_ASSERT((!result_of::equal_to<first_type, last_type>::value));

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        joint_view_iterator(First const& in_first, Concat const& in_concat)
            : first(first_converter::call(in_first))
            , concat(concat_converter::call(in_concat))
        {}

        first_type first;
        concat_type concat;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(joint_view_iterator& operator= (joint_view_iterator const&))
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Category, typename First, typename Last, typename Concat>
    struct iterator_traits< ::boost::fusion::joint_view_iterator<Category, First, Last, Concat> >
    { };
}
#endif

#endif



/* joint_view_iterator.hpp
di32uEmDV9+vbe7tXp1gZzG9s2fT3mby3Bnvbo2wfL83afrmaH9H52XL92WTPoC4g9u2AbB8b65oO9B5IKzXsfJfb9K3xvorbuV806RdIfW0tK+5NH3O5tDeh7T+3rW1G4ZqaZ+3NJ1a+Woj7Zal6fPEBt/HLA2cRfYafJ82NH12gkRso98YGgyPHfNOzo7l+XmVvr076ts2wrb4saGtaZeKkZXzA5PWW1/vm3boWznfMekvXPFW9AOr+9U7xTXtXpml9ceyNxqbZ+M6ndLSP2h5Y0q3sr9n6UHl/AJJu3YtvnBU6/EbKqXtFhek7K4mF4qsy71VD84UcK/gbkbfDaKt9J1Fm9dTTVmX+/qGSHitv6PfPcC3XA4cMx6/6CkBowb9cB9fy7mitXLPSFrZ3d9b77+wwy3mhMHw/l4bhW03NphAj+oVOLtMeiP9akNn39JTh94fa7LSHvFYjrMT+nIfmm/UD6qAQE7/XJxgoAcugLZm2o5dt3RF6Gpv95rJA/mf79J3lsHdCUaxI/+lE3p4XTesET9pq9c4dDga0RkMNuBI44WODD7B8D6stndvGCEjS99p0XVbdEa2X9dcemUke5Z3a0ILzOGkZgXZtnyLE7q3/qr9wZ5tQyig1a+bHaOHVhGamohj9GYlC+bAJUz6VyAsQB/167sH6peZZRuj/PRazidQDnSJ/mOwqV/NtyWDNhxC4g30K/0w4iOwDy0GM5Yt9j0TLIx9ByuqArvYtyNWd52DHSG4b8v8fsTy/eqRf1KQll6+BfGBtk827wHuE86YNq8ap93ku7bNv2Lk5NXdO3/3OnQbtvlPD2zzCyvhcvUdfLz1rTdy6iFSmit4YsfcBdQLmhci7jMWB72wDrm+cLADH86VsYEBHfdh5035TUbt4kM72P3fLxqf8e5g1Ov2rsGqqXZEfIjd93Xo/R1N3EBf/9f+rqJt9q5pm7r2CJt3zXO1f1UfYOrHA/VtehyTf+5BHWieddA/Xa673Ofq+Y6hC4hN6V30hDTOEysr4eKEPjuNfmYR6XNNOvztUmfCf2QaXcsHX/rxHdsF6Ae2C9Da7WJk3u/gdgH6wn0+ArHuVXgxLFZNDznKAnkC/ZNIJyRD+zjQWqSa9nnNF7SoOI/8Lvy8cnZqX2A/q3ceNe29N4bTll4P0y+/y0l/zWswfXhrkj528Dff7aQD3o7FX24bfVheDbqiiiFnnupDOruK9NX+HrgU1D4eeC/lFYZ+ZR88Ye2DfOtw9djMM6G/38igv2v5UoaxJzumr97EWnXD9EbdMJ3UDfHtut0X2v5+oGfeMuw1wWklFMX4rj0N0rY3Bte64+rfb4Z1SVddjC7W9PsDPb4guMU/U+MrBpyX/9PcL2i1F9LfPIP0qe11uajG356ZiXSvjOqQD53aL/mE7sMLd4H6PPa6jkgxunEV9+W2QHZ/tot31Or2Xt/dfeWg78wXb2cmD+iF3fUebJnvrvVR9qWG7Ac49ynXZ7sg8pWj8SsntlF9y+nfjcFoqCMbVF0MAcuHKPfEpVaZce/u1bMH8mM+t2TVLvFKAvOM7f5eoOsW7F69ulv5hYEuPfv5HcCEEHrQbMfpD8tgZ7+/YnyJdftBn3mAubTiXQy71VNfnTr9uZAOjlxByUPcgHw8pAd6jC6vSvNZAHexMghXVrrKW/bycBW8vix/qHEq9LuSL1s7rvUsM2O8LFbhJXw77ktICy8FoVoVZdFdLi+siiJ0y5fnXVNEbzn04FOkde0FtXyAGZu0ov99oXihKHg3EStgN15UuRnX+T7mqKYLsCxqdblOeyHw1Cy6nqYsLzL1u1CYk47oQhHoMtXlfImmxSvdxCu4DLE=
*/