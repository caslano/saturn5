//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_CONVERT_HPP
#define BOOST_COMPUTE_FUNCTIONAL_CONVERT_HPP

namespace boost {
namespace compute {
namespace detail {

template<class T, class Arg>
struct invoked_convert
{
    invoked_convert(const Arg &arg)
        : m_arg(arg)
    {
    }

    Arg m_arg;
};

} // end detail namespace

/// The \ref convert function converts its argument to type \c T (similar to
/// static_cast<T>).
///
/// \see \ref as "as<T>"
template<class T>
struct convert
{
    typedef T result_type;

    /// \internal_
    template<class Arg>
    detail::invoked_convert<T, Arg> operator()(const Arg &arg) const
    {
        return detail::invoked_convert<T, Arg>(arg);
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_CONVERT_HPP

/* convert.hpp
axWyPpvH49lzaWKy9aPlwRk2OVwbwLr86LQsJz7nRcbWapbr9riJD9uXx2FNAI7EMjllutNx0Dldj8zLqyl5L07ryMuLMMx7SVPPK23DtTJxdN2rlcdnt5X4yXzcHaNQEl+Qz3NdJvkleTzifZuh7mHNkwvaFpyxmJcXD6h9Ti2Xw3lN3vx7No/DbySy9s1mcIQhvp7PJVlu+nvYNALNkPrn8so4JV37rueVC0P7VffNz+Vys/0qtpbL1/UCGZP2t+Fpn+j6cps8Y3kmB9rwEuZeKL9fz4W8PHEemTNSrol4zfkk42L6Fq5Re4p4vn+RsfO6iMPLZKzmqv+9Pg/nENfJqWrZf+cnKsvJ1uVTj3B5OwWdCtbZXxDxRlkBxqHsT6utbYt5aoe6vhhxsrbF58srAg5zbXfekY4JeZzUMamfzuXQSHfysN/P7bk4TjMtvvqmNjw6weq67i9rxxVBy7k4o9K3be9hMYzf2Hd5F9vyKpm8JU7OvQenZTybz+WQp8oskTlDPjcjs/l2PJWZ2nAbrrU3ke1CW15WtvL84Stt7okUWsbI9nz6wgzJ+NeWpwYg/daWm+038QexzTCGGPpM+iHC0xxwPq38NI5NXhjxKFLtXWNE86KQ595Bk7WWlwqedh5ZS/x5IMTsD4Xr+2t5OIvOQPtcHgsRpwdp++/bJ5dmcbIwgj8lxO0Pjys+4vDN7M0eLm9sumD/bJ0nhnjaBsXnI7wnOg+8EeFR+cwTFG8FXGkBGlvk4rTQk1FjJuJQCf+d+v4rcvBIzrMxJ62o7kMWXd2cbqrx5kxd8wHmmqBxfQbP9nPvzSEn7ufZHJwspIy5964M8B28StIqx4tzCh/Icpr5BHK4NSjHiaEq85goj3Nb77y0StK6fDCP0yzJi93HLYflpU3bNndr7K6cJOZovK3rOTFHY0/VoVxOeA5oQzkTagd6tm7HpOJqB4rXIzxtreLzEZ7KVfGZpyvu2cG4tDMXRwO8NhSeqZw8O6jl4WQRnHUQc9KKavwj/m7L5uzczJtbo0eOlzsvuy0Hpy5+Hr1fjzkMpb5NxHhTN8DleXVcV3ZyijyzmI3LtfxGlL/7PX6Ju6I89CeuNY/CNzQPnVeoPc1FeejwrmPVfB5nOqG6PODynmk3Yp7G5joHjzmaj77T8zLl+DG5yPV6xV08Lv36EcWiWFzuL3j5uzhc7MzHNNatil5l8Gan6/x7IcaDyXezGRqzmf8QdhXAkTVF+OEOizu1uMNesMM3dxcgcCRLElw2tkkWkuwjb/fuPzS4Q/DCg0NhwR2COwR3CO4Q3KXfm5mvZWbD1VXd1fu+He+enpmenucxN2EP8zsFKZ4b0APoszSHBixzGknOktKdzQTH9mHLcNgm5r2F2SEc2hl0XVo1BfvZ5Uk+Ddby3N1xHwQdEHMxIDPiwf6RPLavc/RVhBemrzjP7PkRN91XMS/uq5gT91XMifsq5sR9FXPivkpzhvdVzB/eVzE33VeCV+kxZ+jm8FUQuM/jTMAOJEY/k9jmDwJGF2C9RRKwPYVp+yB7QcBax8a07csxiF8sOKRplt2lAj7jTeGugEhj/yWCw+PpDMdQljj1/2I2APZSiZEMCF/d5oUvJLAihDQ/w/FZ8Vs6Njo60qL7bRLfeQVwQggmksTr/5E4Zke2Of+bxMttdJ7rswtZDilboYvPbnEdZ2Q7wv0N3U5nQ97T3hnGI5KKl5zisUJge+5vF0zxFuZljKxkWi4d7InE6fAVeJK/pV72IHDT6fVyuvzs/X4ehDk24lb33Kr+ge1yjohDylG8UZ7E3WMx0J8xp6B2VRWA/jxnzE21be3vF4x4tm1rybR0OvWYQ0M=
*/