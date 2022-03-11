//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2003-2005. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_MAP_ITERATOR_HPP
#define BOOST_PTR_CONTAINER_MAP_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/utility/compare_pointees.hpp>
#include <utility>

#if defined(BOOST_MSVC)  
# pragma warning(push)  
# pragma warning(disable:4512)    // Assignment operator could not be generated.  
#endif 

namespace boost
{ 
    namespace ptr_container_detail
    {
        template< class F, class S >
        struct ref_pair
        {
            typedef F first_type;
            typedef S second_type;

            const F& first;
            S        second;

            template< class F2, class S2 >
            ref_pair( const std::pair<F2,S2>& p )
            : first(p.first), second(static_cast<S>(p.second))
            { }

            template< class RP >
            ref_pair( const RP* rp )
            : first(rp->first), second(rp->second)
            { }

            const ref_pair* operator->() const
            {
                return this;
            }

            friend inline bool operator==( ref_pair l, ref_pair r )
            {
                return l.first == r.first && 
                       boost::equal_pointees( l.second, r.second );
            }

            friend inline bool operator!=( ref_pair l, ref_pair r )
            {
                return !( l == r );
            }

            friend inline bool operator<( ref_pair l, ref_pair r )
            {
                if( l.first == r.first )
                    return boost::less_pointees( l.second, r.second );
                else 
                    return l.first < r.first;
            }

            friend inline bool operator>( ref_pair l, ref_pair r )
            {
                return r < l;
            }

            friend inline bool operator<=( ref_pair l, ref_pair r )
            {
                return !(r < l);
            }

            friend inline bool operator>=( ref_pair l, ref_pair r )
            {
                return !(l < r);
            }

        };
    }
    
    template< 
              class I, // base iterator 
              class F, // first type, key type
              class S  // second type, mapped type
            > 
    class ptr_map_iterator : 
        public boost::iterator_adaptor< ptr_map_iterator<I,F,S>, I, 
                                        ptr_container_detail::ref_pair<F,S>, 
                                        use_default, 
                                        ptr_container_detail::ref_pair<F,S> >
    {
        typedef boost::iterator_adaptor< ptr_map_iterator<I,F,S>, I, 
                                         ptr_container_detail::ref_pair<F,S>,
                                         use_default, 
                                         ptr_container_detail::ref_pair<F,S> > 
            base_type;


    public:
        ptr_map_iterator() : base_type()                                 
        { }
        
        explicit ptr_map_iterator( const I& i ) : base_type(i)
        { }

        template< class I2, class F2, class S2 >
            ptr_map_iterator( const ptr_map_iterator<I2,F2,S2>& r ) 
         : base_type(r.base())
        { }
        
   }; // class 'ptr_map_iterator'

}

#if defined(BOOST_MSVC)  
# pragma warning(pop)  
#endif 

#endif

/* map_iterator.hpp
PCq9CRFQpSbhtsLyz04tBIE2Fyvv7OcWNvUtr7ywbKQ5ThY76hE7J7MH4eF76BqF2V68DydonxR/clEoYNCYgQwBMhGwRMZXv+Y4Yw+oOkXiQgiv0bqSB/fqEZ/Zidha+vUHi22UqWez2qmuIG7/BoEVyItDuy5RBC/PH/XX1nizHlzS5QtXSOWAunEKQzN/7nut8I5PXk7edQ6xtk5m3bJF4bXOLfS3xfZhDpQ9FvldTvfE165ZvfoIFMWk8r2hpLLpqCyWo/pj9UBZ1IaZCatMPCeAYyVaeB0Et1Pe4a9nqREHdCAuKi+cYll+ck8EnrW2n/eQclfscKXElpKLR7tbtuVkDQAOneZMXWoCp8uaTXeRdEpr2oAFEx2CQcrKdW6YMa3buNlWS1metYBZjhWeN7Gimbbz338ZLIK8+yGrWGFe2EMN5QQPeWoIbmqWvI3vn8/Oka8nmUkWx9gkLbntawKWSLLz8g4gWCjxGXMovm0QIgWcrtXQCaWN/+WJGa9j+09rY1R0Nd/p3d8ssbI1Tvvn5OqLwGFSc9UWGiLYaanL9JwoOrAHM7K9wT0+003DFyT1ScEBngmqXJnD+a0zJhx1P/qz/CkC7ZitfMRAHq8xLRzMn4vn8VhXpG5YFTB9mivH6yjLPNkIA89yQgIfMxMR2f1CN3vWNznkPGE4/kDZE93G3o/6I/7ibSNjIfEGBosv4+nr36PP5zZti8x/oG0oY2KNE4prhMAV2+vLmBO8arUfXCwp0/apON3cBwJy3i8zsXD9VJNc7HteSRbFTDcWWd0gowbn8teshr78aDWrg4MkeWZyjPs1gVBNdWsmw6wD1LMQx3Aa8Hp6g1rfcQY6pgbSMwjPBiWW1jRCi4P5P9j6ARDBWF5LR/rc/NgtEwM+f5B4ICFLnUfm2LKC7GoNpwJ70DLJ9G4yn16/jFRKZFOG29ACEdEXVuxqqYzYdXoXXoGWZhCnYHvQJPGq2wpPkO9igG2x7Jgwg9BkAs/+DQepgDEEfLam8eR/dFbOMhiROX+Zqr7s79nWruBzwyrGP7N6kEwMkF0/bUnr55BFnayK61j0EUtHZD6Iyb1NpePtBaUPFrFxjMCyYT1N5XtPw6qIWXrOPEozbGiSdADtYYXqRMBZByPoDsQ3bYl4v9TSo1+ycJLf+N3C/NJjBXlyubbTGTdj+jtkW/F8CBIqCPr+o5tkXd6A+bjgqXz3qqIOkDLd5Drbfl1YJLGnwcICmUZHm/1p4fvA6RXZGcAG0o/Csi1Y/h0on9IypZMyzt7Tni/gY6wvmMCVheJGw1nL4yaEDU0Ua2quS3vVHfNoQ4H7GwUpt2wJMz20uqHagVrSyrLF8I75oBL+hmwkEpTPcm6P5jLw4hJ5kBcO0o98oe2EeMBr7fqixdeN7vSKvYrQqtyjkbe5JijiXUj0GNXoCTW+8eulCvJ1O4dLnJgsrxUk9YfqXiziFt5PjGUa1JUVOsCwS7uf1f1kzZzmcPVEgx/rd8pIEP3A8vRg/kpgKoFf/HE7LI15Ik/8HkVDMiXE9vjK8fASCDq1K4grZ/z48/YR2YUoEk2y85LY1ejS+Ciyt2HggEPiZoCctOecG6vcFuVotF4U5Xm3FxCl3fXL3eVje3ii8UFC5OoVMu3LzkBrHVK97iKfYnXHpRieSMHEhCXxR+LLx/HwkPL7CfwMWf+jvcfQAcrhe1I7idBTqkj510cfpZkb+DXjWy7BhUukgPeLzSdvj85fsDOPJMqs9sIBPo9LwwcGj0H8zygWBt91VwmCPS/ZFIe6em4uLmNNfz1ftShrdxZ2sAsiPEinHc0McRKOntP1x1r2el3KexAb0t8bHw5lYPMbmUnsD7FxvsQVCeBKiMQGoI6KiOqeJhPdypyjjrTbVJ94TarvEiBYoCn9hlUeUzyERo9YHPRwTkIjgY/fepUIoNEpK2NU+p3365uMe8PRGBd5nIW3SH/uiW42NR+dNcuG010OHl4Z8VGCCholj5hqepbHfwEJLPbT2+6bLbPTeGe2euZltzvIde8/mIZ8EWUiXg37pmXeNC47qAPK/WX8RwA/LSxl4d7mhuBx0T2yCFbE3EDWwGhaTN1kY49Hi5WPELrxNK79GAaU/vt6s1Ftaq2rkl5R6yVNrlRLDVO9LDUb9VqlUmvI2lXrh7PD4Y7y/Oz7K92sNOs1vVRXriolRTGVktG6qpfqsi5ruqrJinFZ5ILINO2ypSpNtWQoFbWk6a3L0mWtellSK7pSN7Vm7UorslEhG9Vas1bR9FLVaMklrVK5LDU0vVGqVw1F06t6raaZP5wd60tx6IoZArkGxdLrH1RCSZPlQp1kndHzPk5CO+TWdu7YOOUFHxDlyGuyTEderGD+cFAyhUh4hWjfDOl8iMKDje/29khqdq+bg05FtbqvqW+3YzaGg/13/1XnbeO2jZ8XxxolZu8yQPTop9QC3jNHwKdYMFPoRMPZBWbbydkw5Swf2zkfuaNqRSTmW+AK5vDh8f6eNc+JL1kW/Y7Xgxt7QX4vubHkQ3HHaRgGETKCQUxmhC87xpKhPzP0vvkMoglCAqN+qEhSvAVbsyh//tnnn3GhbNyRJTm2j2DZAsW+WCBhe3tFhQOrusLZaEhmY7xwfeyx2zD8ltIYbG2EW0diCTeoRGSZuhFIlgSSy2KTcmmgctx6xI6BOPWlmCRpKE2iYCHZvoTT2qmfSGs3mUl2GEZBGLl2QngUDyfiIPNA9HxCDlT8lIZXLvL0Ne0hDrXAAepeldWLfJmNA5IrNenadaIgDg5+PtfNyqpPyyqWPFwPT2a2n9F8dytEkFAGqVLGNW7IurULWZzLg1wJxeaKRNvAJ53Gpdn5qmmP4vJaKTv2qEmiRME/m7zAv1N+3yO87HAJouuNScTTGGQhPRLabhS9dWPS9t2kY/vTFpnYqZeY/hRHqF8rcqWSzVf5IAGdjHnT6JjXjXZHMEI1mLgbfHNtz91BJogQmgwzioIIOjDSIo0TaYanSNs5BeS6B+qG2pTMoIpwCamClCWua14wdUG/YqplOQSc7YtI6TR7w/Nw0QE3f8ekBSIG0346AYlp5gtRmddbd2dH43K5nHnjyjdNQTNIvTErpYigPkMpgzLY0VaaQBZ/TYOIH6TTGdQFchg+xp/m0DX0LC2UAop+H8QTcToNvFyG7SvQkAYu8ikyitjsda6gLjY617RpoBMTNIVIx5m+f3rdt/q2H1ugfe7E0uUfROpoS01T95tY1DkJXiF624NUjrdCDDIuS1kZpr6wC2i5CG/upRUHGJEJdPsEJ4bk0MtSK5C2gLXG7TpQ6g/ABRNg+naftIGbeORD6VN+4LOBHfON2bkOxu5ke9trXzd67666HegVYvJR203fCcbklb2C6F6T7SAK0pFHrGGvg9tfoEYn21mShP/67Nl6vS4nxJnFC7BqZSdYPAMDCUbSScp2HH6b2NGUJM9xOeyObGfEC5+GrNpQPzd5Col5rihluSw/9SDm5+bN8GnwP6w9/W8cx3VnyXb8UTixmyAwGqCMGQtx7TnMzM6nlQSe3dmVLuFXSdpyqhOII3mSLiB5LI80JQiCW6B/R4H+Hf1L+q/0p763M3u3vL0lj1ZPXu7sfLyZefM+582uJ3+8HJ2Uqn660z3b5Yb8Yndr5/nFOR7zCkdwrz4xbBoDDOvuz5vbjLmtrZ1SjdbCEaFbMCLKDl7UfpgH7V+86Jb//TCG1b0at7gaCZm1LDd43cYDmEbLxn74+/20xbKpcl93u/edy/4K63Ar9J9PQNP8MDh4GVD8uBrkEzwiNz7hOuHBwwhi98cgfIHWL04GsO51fRfrjSMvBv27gqorBLQrJQl8soKC6PjiGOl0psSD+uvlK6IL2gdEFG71n2EX+1POCMofOOFspuChjys64RL54bz7I/vRbW8BQnobxaZLN7/dbcMMVHuYr21Bxb/EKlFpXa0W4jNlfBGWWneBRhBd2eZG0XuAUQAw074bDR4N94vx2fFPZ4kfRoPL4T7Ig+N5jpiyQY01AkeAXhpPRiDXX/b8K+8L4XiSEOm0JyJzgqQZFURZL3XBZOGoe41DryILf0A99aew5MxIYQQT0mBpDDf8SH+cK7XC8kW7BAtrzu08LqhzdRcTKqBJisd+eydPxz8dlecXh6NjgDICKMuLl62e3wVFhOTHeCLkH1ZXV8nn4fenb/CH0jA/RHxHGa27CUDikl6xIWJhTeaAm7i2tr7TA6sY6WjdgZOQbwMJ7W5vlvnrOw+/3fWbjzbgwfd20J3cXo+1Azl/u+Xdbo5EHbTzcP/iGQjsYUBpsj4YnWTjk4PhKa7F1DPd2tzeNdyaOVd1fXBy8XRwgCGys11A5w6icyUbn6EaRnjRlMmgg1eWelpkIiVeyYSIQliSplaje5Zp4STPNXsdG6CuuBg8G0beZ+xqKBcQL7rJK2kyLkVKSZEWHF1LSqxgjvgkFVPXMrbE7YND3P0+7DJrJaEGl31GBDvgTp8NM1C24+NILKPhxHm/tpm5tfuVK3g/ymdg5SoZRXX1iNWqdFy2+1E7+t72/SAG7odzBhubj+5fDW2Ex95O6ZSXD1PjLzxdjcuVeb0chgnOV1iTKq/qu5LJITEL3ZbP9fMdZcaiAF8omGqI8nE7fwCDzLf3SvUet292yqKZag2PD8Gj9oHsQkYIN8VR17OmwaoFmWvr00zdaFsL8jXzai1No2UtlNfMq7W0jZa1gF0zr9ZyuqsVcmpbDCFjeuCkfNzddhs7xeZ2aD/zrOce99BoCei8Gr+9P90NqVJokNxHogRLBeksGGTNnJ3eGlBsmb/h1vP1yejh6PBweDJjhhrp4+7a3s4/r6H6Aq9/Fwy8F1uH+1uD8+f+6/5usdO3sh9Uej/w8CP0V4ISLj8kDVoav8R1cvC8n45OBmcAv18e9eqX2ngvtNp71Pu+ezl6cXq4/7jkjHlT+8k9d4KO2srl8zH61ZNgPgBrn16A+t88OXqZXZydDU/O0SNpgYG1VkBjrtw7Hq78/vHa+Nn4BKs/+aK10wsQE4PyRDg0Lc9prqAVA973EWSWL2+V7sXgHJ2S0ugG2wX0yjma3OC2P0XjJPjxcbz4wYruVXuTt/UP9nzpF4WOa512V37voCfcEw0Gzf5se6HbOp3eMWg38BKjuN2HKY2PcJsFvYKLCX7S4nBwPtjYbB3P8GB0OIwm1+Xz4UkFCuYG/hW4G8/yHwZHF+UgW4AU6KDdK89TtnWzhscGJ8PDr1d60a1dmcSTbivgBtSazbssT+7tvjzF5bquTnavFP/XggnOTXDkr614c5Xte+XmbXVWr1/tcA8PXW1FAxd1GZvWm2raisMY62eD08H+6GiEfApabg9oYvJlldg7GJxOWA2oH04OzkYliX3z2eOZdnoSAAbbZHs4wSOkn31FuDCMT4Gh7703AHPrYG//+HTpUfXRpHHYbBRJFVtXk+tujYIZsaAXUMzdA2TiZtHw+GkXroVFp5MuXIuKno3K49yLikYH4y5ci4r+dvqsC9eiotPwv5FfWITf8JocLio6G0y6cC0qQiOzPOu5qPD82aAL18IimNn54pldPn3RhWthEWDxcjEWL2HSl7VJIyVVpIAxTIyLGrh+3sH4a4iXbnXudJ7A9Q+du2VeiD/e7XwBeZj+nw5+q+BOGYvGdt90Quz7F2X6rfL/I4QxfIzDYoz96xgjxdgpxp//E67/gOvfOiHmi3FcjMWGmOzdzttwvdUJsc1Py1ToB/9h3LKKL7/dCfHRj2LeJ3C96oS4MLZ9J5a9H8tex/o/K/tEqKHsVxEu1vmvTohPV/28G8eOcDDmvR/TH5RlmL4LY7tTzr2C92EntMM+EAbGyKs5fhSvKv6OM0W4vBNgFbHsvzthTfCcAML7TSe0Qxg4t1/DNYjw78U7jgfHgfVw/Fjnk3hhfoXPg04Y469jHo75l7EOxs9xvn8fnxHWz+Id8xHnOC7sD/EW4sohD2P5WO/dMu9uWQdj60gz/3snwKzOF3wPl4ztMFb9rzG92cHY+p3y3/1OOA+ANKrhCuclwvVuLY1nPnAOX5RnA5BK6JRukQ5xnl/DTHHsHwM28PntmP8md8TVO9D3TfWqe4XDP8Osfl5SyEclbt8v0++W6Q/g/lVMvxfzEceI6Q0oxfzqwnyE9V4n0NJ7MW/Z5yANpgpgukXfj5sy1X2l3O9cwU2GM7Qo+mtjUMT+4vh0Eo3DEPQOzhfmF0eDZ5NVenC4B6KGY06GEY7VJOQkZZ0xbrGvfv556aBFU/bzOTU0Ou9nIGKfl52FxgLTYAwMV3nI2APLgf3T/8c0gt7EqQTIKtx0uJlZd/zNe8Pg0qwnFnHFWLzX5haRxkS8y3iPo8MqVVEcIrMR8xEqVomteATMI1Qem2IVtfNXcAnX+9Hgjm9rgjnfj8l+ec4g/AVHPmINvPuzeJzNXGdNVJWE5IeDg8OD56imZpnsfPRscDJ5cDTeHxxFVwP9kbp5E/ZuArUFyyx62k8qOHoWXq+yGI9534EDcXUf4snO+QAWZDvW/AsQUvsMQt0w595kGuqsPMIFpBARGTvrgwG3gjMKiKuOikyHmUgxhZUdgfoGm6uHiH46OBj2XxnnteGJJlw6T4SmGTFZrklBi5SmXsmCmtewNuMXL3fOL/azo8noMOGvKKWcCi4IJGj4k1Wp8BPqdW0MyZuPAZlzbbTPurQGl78S1vGkMCmxLNUEnlJifJYQk4tCqiJLmXb1kbDrRqKctr5QlOSZEUQUWpPU2IxolTGq09RRnb/uBTx/B67NGK1XHFj8MketH/rG/TSwPoMu7JtDj/isATW1tL6uA5rrIsmTlODpCSIY48TlxpBEMUWNtoUQ/gqaqrf3qw4SXVtEod64r+tQJd8cehNVopZu0na2ttPz/Vc5ZxnlPCGppJKI1AJwLyWx2vKMCyU4S14D+/b8K+3yNOG4C2oEjEMlCYyjAHr2VjDti0LmtEbFogqglNidfRyhHECtWpPYbzM0QNTp2fgAY+XDs4TvPsdIJCgd3Bg+cqeDs/P6mkJ39LPHq3Uh9OSzWWHSJNlbjQVW+FkvvgPZXUBa3akmgL7Mm/XVWO+kyQ63AhhlNb7hfzqEPyfnN02n1neTPWLfPpVAqzonuXcZEUlhSZql8AhSUGrppbK2RjSJvEI04dXC6ptC86STNLXGbXqdI50a3KSW5m/WxwIchkmVE6w+llSni1Z+WK7DJl00pfytAC5FF805zQbAW7mKGUmFlhlhiTJEOGpBQ2YpYTnnynGdZ9LUiIObK8SBem0Fp9tGH7yVI5bquJU+uKqlm6L7Vn208dic0q5TCG8l++W6bFAIb9UOywFcikJuMEWu1YBLGV9Rl19HibIppm6gYjRkYXo1EE2auhEE4nI5Zqv101QPSzOcbDLcjQIojHIGQzWlxo0waq2bQqxdjTRwrJoy97rWJXqX0nG1Lpokv4yeU03Wu07bN5DapPLljAV1A+EuYq4mWm8g3cVASuwuJQdqPd1AvNfLAnUD+S6Wj/O41jcQ8E1SVrOaAHLGpgmTjOC5DQIeuyAGEEAYFyB9pAN2TSoB5CYvTw4Ce9Sg8dtCu8Zd0MmtgTVkvq55B1rW4DHlMmaNAlCZA2+Dgq+a+ZwIjufTjZLeT2VtRar1sanbwrpuovrWwJoTrXmM2tYRB/CUzxjQtGVEiAKUigOJwcFiYlrK1AoLEx1heLOHpzPLD3TMgBl6W2DXzNRcobalgDVmaurw6iTCmc+dNJpkhU2IoNoB5kCRekkt4zLTXhfNma4BqOFJXYAYcVug1824TnTLAWvOWJWeKbQHR9jkgCdJaUHE06dPQfqDvQCmjTE080xJ9ToctdrC741N0F5ZfUEZbgIZquJ+kJ5tDZU/JmKCQ7UDuCdzZdUzKyFVP8n4XL0K8Fw9Opir1wKPVuOY/zFa64nK6oHTmH9D+VRCNjfwHu6ur5UfpQ0YDvxefQWo69fWXiUaUExNQoDFNPCjz4gVwgPOgSvzrPCpllOdIOiUDQW10ySj8Zwduuurs31SFo4PbG4/cBu9fymPuD45vRyfHI1Owu7ndr6Tr+EJsU2f72092txY623MtkIZN/r08nx4xBZV3s3XWL2qPb18Pj4eng6eLYT9cHM933IPrkA3JfQwyCZ0/mRjjMcsvi2/VbUTjlTOWlu1MS61TzY4LT/R0KhgNsa9YxhOawW9McaPS7WWJxvj7fAUgubxIPt8Nbsxjjva9ZcsmvXkxvjRcL+1NzEFc7UKHvoBzTo87J2slqiaPwU0RakSOnocNnFZqnJH0kIluMkkickzSpREf98464q40XI2OD7Go7hTGIpHAdF/BTIyZ1meEq4NyhOviGEmJTqxxok0LzgTr/usS/vTPT6l6O2azxqy2zXEfqcvOE5PFq1AbvBmUcQNzl7OcGNvhZs2b6zZZXeaVR5cmnYoTU00pwbsDWBoUogCDOvEU2KtocSlwmuamlzqmdpdDgGzmSW3mdlsfMmNc4l2axvcKh5oOyEG/JvO5/AcYq4flpFHjJe+W8Y5P4ox1g8675TleGF8GGPL+O4/xpG/iTHf7Q7Gf/+9TPeg7G4nj3Hq4/LuOrP3xLfjHev9XUxjOcajP7ymzh/LeHoXYH4Z48yh77UyqvoBjPX98vnjWO474Z16TOcRxnedEOuv4OH9tzU4VV++E97Pn2/7jzFdtf1dS9vVBW1/G9M4109jWse76oTvFWCaxjwT73zujrHzqu6XMS+JdxLvNt4RRlW3av91vIt4x/4+iWkX76Y2Hyz/xQ3lH99QXs13vvyrCPvOWyHWj3SHZws+vHLhyYCQxnHiuYqKlpBeK9jVNwzq+dWZjl/N3X8Z7xWc38R7VR/j9x923o73gE+8i3jvxjvidDWmca2RZjBtyvf13ynTX8U8PAdzL6Zp5055hiTUDe1xXT6N6XpfIT/UvR/vLt5X4zcHqjaIz09iGq/qGw5JvLfIlbpJupTc67VIUCVurxL6xZp7sDMDIX8CCHybw/e2H/9u+lrBTEAeHh3N9K2c2mBKmNsI4XkjXKnkJ4yT9i9HJwl/vHrTOIW41eAW79gqWfcjl1rYVscF+rtR+XQBCVcyVjb3/wZ27gzGzOoQLLowSyGv2fUM0GyIggaYCwYKhvs=
*/