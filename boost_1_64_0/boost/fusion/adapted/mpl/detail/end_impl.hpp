/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_31122005_1237)
#define BOOST_FUSION_END_IMPL_31122005_1237

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/mpl/end.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace fusion
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename mpl::end<
                    typename remove_const<Sequence>::type
                >::type iterator;
                typedef mpl_iterator<iterator> type;
                
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence)
                {
                    return type();
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
53vGZUA9h5fKMvUy3iFr1Bv44m79q2dxsSxXL+Etsla9jvvPVY/vBafIEp7HlbIxvi7eI1u0Dz2uK+vi6+Klsim+Lt4hO+Lr4ot73TvP4mLZykt4i+yKr4v7F+wN9QinyDT1PF4hbeplvE264/Z4wDz7QT2DXXKhehGvkVb1Kj4oo9VDnzmXkepZ7JdJcXu8RobF7fFBGaEe+n1/kWVxe+yTNXF7/IxcGLfHX8py9TCgvayN22OfbIzb42dkVdwefynr1MN845FV8R7AflnGi3i7bI7nDScssPfiecB3yib1Mn5btqrX8VkLral6hJNlc9we3ynb4/b4bWnidXzWImvHI5wsO+L2eIVMitvjbdIR94/7L7YWcXucIgNxe3yndMft8duyJG6P+7/OHMbtcYqMi9vjFTI6bo+3SVvcHve/wHMUt8cpMjJuj8++UD/H2le4WJp4Ca+TYbyOv5ehPPX65nCqHMTzeIW08jJ+XXbpP7zB+1mmHacffOQi98jzRXMuAzxcbC6XuBdeeZM9LJv108B932z+eYSzZBkv4nPeoj3P4k9kqHNTSz0Xsko9h4tlBy/hvpcapzYZvFSG8RreL9u1KbzVGGQ5r2HT26yLNhFOlDXqebxU1vEyfknW8lrsy4xN+3BZc3j5O+xVXsN9SuYhHj+eJ1t4AT8h63kVH5Qm7cPl9qdsVc9iv2zkRWy/wtppU8ffyEgelvt+IeN4Fs+X0byIq6WVV/AOGcEbuN+7nBuPByfKaJ7Ht0kHL+MGGeA1fEDaeHh3c2iWcTyD58o0XsD3yYW8grdKN6/j3u8xhzyLXbI8HhteLWt4FX8kq3gDD1thPnkWXy/reQlvknW8hruvNCc8hTNl6/HGjCet0idv4Ofer5/Y8e4POJdnPtgcvinreSh7N8pBPItdMoIX8YPSyqt4jwzjYbX2Moln8RoZ4HX8vYzjqSt9L17j3nkd533YfPIyHneV/czrePDV5pNncK6M5EW8RqbxKj4oo3n4mO/7soXXccjH7VWewlGyg+dwnmyK5xavls28it+TZfG5OGStNeIpPF5W8RxeIMt5Ca+TJbyGD8gO/YRPNIfnynYe4RjZwnN4gTTF5+L1sku9hrt/0vMYXwuPla1xe1xTMU717KebQ+oa68hL+OJ1rjtaG1wsTbyE35ARvI4LPmtdeO5zzaFXdsXzhl/6vHVUT13bHOoywHPX+RlJpvHMF+x/6eap692jjOYNXLnemvIa7nODMfMIPyNtvI59X7SOvIx7f8l68QzeKON4A1uq9gnP4NwN5pnXcMSN5orncLGs4SX8lKziVbxHlvNwk3mQjTyHvbKeF/EG2cRruM9Ge5tHOEU28zxeIet4GT8vy3gVL/uK8b/CvX/VWsiOuH/sle28iFfLVl7Fe2SY9vmbfa+RkbyMN0sbb+C+t5grHuE0GcEL+Ak5iFdxw9fMD0993fcI2RWPE6+Q1rhPvGiTteBVfFCaePiG50Um8VzMb1o7XsLrZRqv4UOynEff8mcTWcZzeL9s4lHNn0FkIy/d6s+d3zY/vHqbP0ttNre8gSd+xxrxPK6TzbyGe3/XPPMI3yRbeRl/IKt4A1u+Z015Bk+SAZ7DC2QJL+H1ciGv4QfvMIev1Of3/RwuI3gJfy4jebjTev3APfLMD/05RUbzCu7+I3PBIzxHxvECXi7b47Hh12UXr+PedWvNIzxFWrXP48UylJfwejmI1/B3Moyn7rJPpInn8JuyhDfw6J+4F17Cj0oHr+Cd0s0beOBW88AzeLks5xU88KfWiFd/1hzuklW8gQfcbQ55Bo+5x/zzKt4ra3n4ue87so5n8FzZyAu4UtbzCt4pm3g=
*/