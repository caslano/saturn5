//-----------------------------------------------------------------------------
// boost detail/reference_content.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_REFERENCE_CONTENT_HPP
#define BOOST_DETAIL_REFERENCE_CONTENT_HPP

#include "boost/config.hpp"

#   include "boost/type_traits/integral_constant.hpp"
#   include "boost/type_traits/has_nothrow_copy.hpp"

namespace boost {

namespace detail {

struct void_type {};

///////////////////////////////////////////////////////////////////////////////
// (detail) class template reference_content
//
// Non-Assignable wrapper for references.
//
template <typename RefT>
class reference_content
{
private: // representation

    RefT content_;

public: // structors

    ~reference_content()
    {
    }

    reference_content(RefT r)
        : content_( r )
    {
    }

    reference_content(const reference_content& operand)
        : content_( operand.content_ )
    {
    }

private: // non-Assignable

    reference_content& operator=(const reference_content&);

public: // queries

    RefT get() const
    {
        return content_;
    }

};

///////////////////////////////////////////////////////////////////////////////
// (detail) metafunction make_reference_content
//
// Wraps with reference_content if specified type is reference.
//

template <typename T = void_type> struct make_reference_content;


template <typename T>
struct make_reference_content
{
    typedef T type;
};

template <typename T>
struct make_reference_content< T& >
{
    typedef reference_content<T&> type;
};


template <>
struct make_reference_content< void_type >
{
    template <typename T>
    struct apply
        : make_reference_content<T>
    {
    };

    typedef void_type type;
};

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
// reference_content<T&> type traits specializations
//


template <typename T>
struct has_nothrow_copy<
      ::boost::detail::reference_content< T& >
    >
    : boost::true_type
{
};


} // namespace boost

#endif // BOOST_DETAIL_REFERENCE_CONTENT_HPP

/* reference_content.hpp
iq72CEUlpK8NNsa2Mayt5Q3lYyCNAK4j8fvUWwI2cJJ9Ckr4pf8nxfkh7OhNxE+mMb6PHQDQwiM+f9RYycITgnUgeaoZPWa+Belvpj9tH0puRdm3WDEgVqoQrReuDBlu+VxMkYcTFBPvg6D51HWcKgrj+Qm5XBA6TqlIeiUcRoiErhtVmfUBAa5oqLAqeiezfrpiPY0tCrWRrtS3bLb71Vc8gd10t/tHrqMzGh8KVMh1cbL21UGxAI2MYrt33HhF1IL2xIm3YaJKseKmT5oUBmjbKPumCch3UwLfaAmRDd+br7Z6HweQbqT36kKFSKBN+TMB3ARVL+9fpkPGoaLSMIGGU55yOZ1D+3rHX2gdG/5ZNUyKyOA78SlgByTDrbvHhgyZZ0F2fnDfoqhTwaXJLH0lSQexsJK9LepAz9NzjGr60zDNldiDz6nP+0PrKYB35HiDuXDfiXETC5B5yy5jNnFrHtbwnRhgCz/63dbItUB3DJVQbBPvNHeKW5XBl0vKbH8NQcAc91nLz6B4Q8AaSJZf/YXjn+BGQ0UZeMq554XAF1pHabZgw56LluuWSqXFcZLdNMlKvnhUr2xEoZeyPbu0e3pKSpi3aI0+jBQbH/yAuFwcNU8cAhJCOfN/Yvfs2bw8LN8ACQIUEZs9+GfZIcAKABFi+XneEE8pSMVaiG1E6teYCHLN+nmOwD2YAPr4N6ES1ABx51UBTY3xir/VJX2iUXiYa2DAqPgTuQjmvoJynr9Oh+Oz1uJBnzMOuvITmkLiJB1IRVOIkCxph6NHrqNBifBTwnLuUZSN+2dIpc84npdIiXYQSzelHnPOsLlcB3cTxoyDK5jLnMQ0/BBljS0B69Q6jiwjiloWH/w9aCGcCaVNFdsejqGigcN19fNtdA5QyHhwJ548+my83O0G5o0+xqzpN+ew/Z1YsppjQTyDGi7UY+g0j6VbJP7B2nh7tGY2bUC3dcI9pMrbqY+BSb7T9r7x5ERazWsWvwS3MUp7Dlr1YzruDSz+j/jiggXWFCogi3YEIkN/EPVJPKw3yEsH9954tUheiZLyPpFL6ROVm+X6UE/wuYlLqLpwpvv18Osc2Y+ZC4KkevD5DqS35kEEwqZO+Sg0IascjoJ1TuS4kl3w8fkQOtNTlZ+qTVUis+d3YJzwncf7HYiY1YiyGhazjrJVDyKrpImmhxilHYm43FNNlgo2oThofNCUon19VuYRqo/pDTwjO+liG4V7Gsq6c/06Oz1P6guhd7uFaWTQ0dwYaUrLAZaQNS08nLQjWKKvBPIVHCxWEPqA5i/yjYpdPj4LLEL+SjX8drVWOsp2p09WBTXoXmwsqk3VMVXxdDKM0DrIkPGJTU8vWrCSHCmZmRTTUCr4fSE5/LhznTkXvp1y9JKijjTX3E9P4hB87jzPXGbjRelswGZWIwHQTSY6YymY2p+GkTu47nlxmsYRUXWu/l+SqLWbLP8Tj5PnNga49liN9gc6fpgtcezhJRdmexYQ88IAgmMQw3xtRnW5xZLySg/pnOPCGNBTmInDDdvJCTmaJbuI5XbPCOMB1TthSEJ+dzNpXjJF3z5GKS6Np61F9MQsErsP8aPG5E8MxccEwEmN7gWnuv2WZVM3B7r5NBsCBMUn7wMC9RNuJ/smswBG82nqzwCbXUST4CoSauP0F+2ikApMsfsd4Cml7L7a+FRy6+1XXsSzeHS4T1bPc88SjvfQy7WBT4o7h4AM9kYaakfnhyYVgdPnh2fPN2PhnENTMhW7vlTkaIn2gtZrBPC5wKzuDcua3pLeqaTts8kqIhgE75+6OhkI5R1HIoeoU8rsk+iMvnDPrX0PgIT5hHr1/5eLSY/YXlak5btJWAqBtEma6qbdkmgydVnW+rF8Uo5vmCRsPHDEaXPalY80PSMA2RjAzpMdwkQX/24JMlNHcLW6Vf3J2Q+dJP6DC0JcZwbV9ZzMlI/KG/5WaaE120tXZAWgldsPErJ9s9q7P8WVTr0c/Z3fpbX6mcp3gT3wsfEETDUvUYo5j1KcJ5zNkz5qrsQtCefVyX+Qa+4+1Y3i5thzLTUOAruGoXqK6GpomDSxg82WzXea77t81w4aAmIxAkNv6DsFfG4iKYlJ/advu6j/avnLPcoe179Ef9sbdk8JKFJS8Mn9vX5Qc627t+ecWIJky5znKio8Rf0j+03M/1ReSGnS81XEhlaTazuE/W8URrb4fjl/wjsUekDffom020b+LLOdQZ+OImitjyaMwIgs465U5+UmKXioU/VF6ax9PuqiPrVsCHHeoJNwmYd5G1f7MLTyF3S0xuQ+fINFC0GZcMOJqXy3/o28P8ExJ2c1Xe40q5yXa3ueDVKxWv90k0ovFyMrDIn2jWYOxvEFjDAo8WvfCCRI9+KAj22Q0XR5T+WzLa1NJXrIVL3BLGtEQ6BaqxBftGYQ5RXeOJuUdX9L17zKIhyTft3Jl60of0zfJ8QAhOBDtndHiQ8Zp2RcuYpv82Atpnvj7kF27Sz4fFIKiif+KIZdGe8rlV5xHpSo4wenNKqEUaN1ITBYT6NyD6HsInQ0mOUWwK5fLbOMwh+9uK+zarZVpBc2PEAx4qBwos+KlQeZ8zKi80lxvRna7OOyglwbp1w0r0F/QVKIUxMSvyYqX0aQKqS+GWjuLrqDpAauVEzpNxxdajtwyK4Bkm8gCXZ038tFBMaX8wfWbhmo/2eDZMXebc+bs+8OHf4lQK16SSygRWkgsTTMO2EQELbPz8PD6yPdYcebNE/0vZNc/S4Qq36mvOGS0KcFtaW9c9qxhhFUKRmbcdkbqIKHLXRY/AEl3IIful5GEIZxGUbkUZiM43v4bQSZh6EnZVAxqDX+4Ldpr+P7PhJOxgwlishsJytViK5Be1kqAY9L20c2sIHfeesAwFXSVWtXD68LzuQlxkIDzCIgHZ5g0AuW1ez7lVT5A6TwY7jVJFzcPbBmnNKz2yyBCy7b96TGAPXPJOwAW+L2bj5tZRXqtraUbSSw0LyDqKHR3drsv9JEGu5WBHoLOm9P82CjTV+ZFHr+7lFGk4YfGgbdu/eJsjWwIbhheFjccBeSN7tOeCu1kSI4HKfGWC2VYsbPVbHa2Xotdf+/JWHhsqDzybdJTDfcl17DLX1p6/Q2QTrGjuKXRBi5s3ov0RfWMSX8QAc8oB0safzdCoSc9m9INL/qTDq9LCDGE7Dl955R+8MWe4H+Rpff4YNkNXfnZxbCQT6nKb5davsG6Yio4RmYwPynPiUGwxvq+2IMsUiduwZgZJqJDeQRUTB28DnFBIlN2W62bBPvz640ZMqhVTnEivnKTG5Nq1NMUm33iDQfdZ+2Nq6aTvu+2FmXTUgq7zOUY74EBVTuNARPFX2d2QqTrLFgzA30OXpUuIEQ+yfuS/keSxBFX6wRPFfGspQao7nowheJmv5z+gvwKvKn+omsGPRLcoFK71PFIgxr6YBz7a2pZIs1paV09IoRq0PPrLp8pkef/b6y8a25vNbuuCrYrsWCfFwWgid6zt/Yq+ZmMLUeM6WUuudcstmj1SjJT8Kx++Hb7L7tUtqyYpmrAgGF09hzNHn2MJrLI/kzWbcXg6qUDAGXlTuK9ZqAvgq9yYVStgw2BFMDvZ+p9OJ3gDCPc4EN9rtweqw2xvRU0No5hovCWWaka85G5Fegqj5OakiH25rK3QtLfBHq58RTWuQMM+s4tUqqXzPcELXsrU6lLDWkBS4c4p5qznr3VTwQvXzR8vfA44rb6UFvWbaX4twwYnmNc3PZNC8LeZMLIhflFLuZXwX73QHfGxSWjPK92zCDHq5+/XqryUgOmDNAY/2dBx8tB3LF3TE8nuWbVQvc2oL07kKwbuBmnYGZdCaklEj0OBPVnv1TMv2hA5t8jj1dI6Ku3VqoDB0vIys4Xq0ynywcUw7hI2J8AsQRyy1PjV9ngEQmeFy0jVR3F4B5sRmCnGv7u1BLAbak15hufSOOuymkZaqRKQv3F2Dbs/NZS1lZ8ZUoTT60RZ9dua1qB6t2iiPB2PnUvN7VVnO90rRdOz68fwcEIYxIIKpLAqS5hAXtQB5KWHgTFbD3mEcerqzwvQDq1rAeS2UxHEPva68Cy2G1k+JgYT3THdqLtm8ARv4vdEfuZptC7GbK6M7Zkj8abBkyyttLpuSfm2qwnuSuG07Og9Cyj72OO2NdwDlX6BpSmh5iTPFTXg733yOXYOr7eg6cpYopV0ryK/QYq3IQ57DNK6PgoKsvH1By16OgMnzv3iQBjWARxxlMTYdC5TlICkwBsfJZ/owMboFoEMo0QL4uc/7DJXMzomTfDl8NrZM+6D9WQ9fm+YHInlhTwCqS40OJV5E47PmRucqV/T6x57rAmoW7gkk9yPJHIaqOaHRtRzEG4xtqEsgJLPHZlsnIH651Y6MGJnRoSWkFYV5oVIxKHeu29fNoX8CVXdV5YhQUi+G6vOF0iEVM9P1jJAK+PYKbM9tnxOnvUU73lP+yXegBGe3qJkLnxPwvxMpVhSm8g11cRvQ+VQ9DbMrReGq+Mq2UjEqRY2yDLeT0uJEtIXhgrVQ6RVVv5RGoDGV2kpz+E2wuIpFBjujuEiXUPqCKZ2NvE5jMlqMTSof2VTFHmMuOmB7qXXp3an9wkNMD/a4EQLNmN6YM/KuDSA2my9JffaB9VQeHG43B8CrKqTXdmjL/EP5d4+0zPJ1RO6h6bOUrQVwK6Bn3O1ZeL2qwFIFK4L79I1ZPQIiEzxgFPxsWvKyeuizq+Jo55FQ7dPM+lsXkM+ilURShizAZM1bC5n0P7LHX5MwIlEENk/wkrLiLAWdJZH60P204soJTgLc7Sf7MkcRIeoBRz7GXqXbx4J52+z96cmcOJ8g3yItavPIiUYPdcWR80Kf84b51hi7cyKoxK7Lhnn1g60oCGJzzzNfGv9wXl9uA3XjSqQbfOREM/pd2N6y+bShhJbAu8hamk/nVw+E18PZynNcq9ZgDxo8oYhgwpNB+MAVoxWEPoCC97EmaKKCzDsCoxseURXkn7O8jsuRa0zJQJDuWrTBG9ZzaPZeya0VL6xec0BsDvFHo51IXlRK4F82HtB5WR27H/xa/Gi9N49l0rrNaD5xIJgQnknpnt/GLE1VYMeiuShvtGBHxkEgReoPJqvemey6IOo5jVFs3ah3tHlsC1ef2x+Ff2MJSaLZ+uOG+u+/N5IWoEzPumZCKSHbdihBTSyQ6u5rHUwhktg4xd3HtVb3hxnFhKOvtQdCxwyGi+K/Vw9xaSkAD8VZhO0IztJ+Qcjc+SuZ4YSIpCqjDv640cwEtsfTLUl1GKHR7p8dBFF9HE9Gw0PJynQzR7i+koaqLK16XG4ye2KDcLqQ+2Ckd6uiS0lmIkow8vlRh6EIeFPKdGQL/YtUn1egEF9vPGyJEfRPVYrOiUlBqpoEAE4C2B1B/3IGfsWhavkmvp6fLj8V/FdKJQgbFDEhx5n4BCK0+YCwPKlKBtzI4zdE0ovrSJd5HJDBEL+EawyhLB5YGTwYF2Nx6OHEG8myeYN/Vf9hI876LdP/cB6ZZkouBiJnoTyx9AEYdmQsfoB82cXRTWL9ZIiJZ2A2oQ9qxnW9JmWlJUicw1eM1i/zvoBBB4HmpMr5O0q5aG/p9tYOOkgeqrr4k90E8AvILnU0dQ3Or9/fxl3tyJ6yio5fEKH0FGth2TzL4LraSrbxK92rr1zUZWsZfzAOjZMga6b/K+xF6iE8TUmFJcjUhHbaolzn7lDkU/7XI2VRhTrN0kz/icIWakQFspMBCt5E6dJEPqiPhHcCKtMxnGX6m+xBaNwkGwPntHhjKgj1elZBc211uPHxVdq2sqpRkVeoK0LChARrNLX9FVRguDXSM9MyviOaHkFL8pbKwutEgh9gdSsqjy4cZDl/HUbpIHIcpe1sKgcOS1DwL8AqUw6oPY8o707n8V7dzaHQVhPiBbxIUIXg+rTuyMYdbPU+op9Zm9xM6/rFo0y865fbqOT+bJ3281+b7ytThLiXa6RTRLZJoSLQTSCaRsangNdYUPQW1g2dh+RradJS+v3Ky+r5SQV4IjOVabAr9TUhccwh1R6420Y7WL69g2gZuhHw/9dX2D46S/jf0k6HjPB8yFuji+A5l6zKjPNMKbgCJLCFCXK9J9At6JaoAG9zxrvT2f99RJ5AExnonz3qzQixUBuRpqXRSZSlVKE+7FUlwvG1BNZv1jgj7qv5AOixnsGAoIqlQO85YNMtEYk0ebfkKTMN116GnJXabq9ofZMj87+srVNzYyOXhE5e0J+vNCzVdXjmAzOxU0LeOsM449mUfkJa/y+ROuCLOWUqMAAjSUseUxsODWU7uaFDKeB67mk1UVBawsN+LSpsKwzDhkHIaXPF5OXcDP1CD0VeQCWYshEQPyLaf0hZmSdLCoVWXU4xNVNb7YqMxHJWlgRAjvGfGvEYfJX/Ap8GNcK8wPKUIedjYH4BTtWLGD6pb6G2MpdfY1UoNwUvgSnA79/079ptPmIC3tcjA1oDHK68ML63gIF/jil7lCgTcdh6jPaQO2VURHmpF9XQrYOc0qdj9TbB0Ll5P98UiGSUxuvfvWhfa+dCXGpG6VdyM58tjPXzGdFnItV2/h0yG+J0weGUMEUvO2Rk+m7cTsBcLQpJADZL/CD/U2ohbFVmrd1Oh5JKqzy2IE6+BSN2pcxv+fMveabYnPKZPkTP+TMg4xgIhNa4U3UNwIAoMANDatm3btu12a3tr27axtW3btm3b+v2HN5NjZjJJJqeYxDPZPPQPl8sGv0SbWh+Ab+fSPh8BDNHAWqsx4xlHJMSyWdu4Uyn+cwrvcEaoAgMVB/USyVhYN63yhUC7Ze+TB6uadM878Nmsj0Oa72ajF/MHLJ3Zv3h+cGKnQ9h4ws8b/AyxfwvK9HJlngDYoicLNobMHsXQT9TIAhgt3wAycsMuW/2Jj/BKBOi4z03QZ8vdwJ5Uh8v+xLZE8LHeGENLyf3zPSiGiX67W/IsKlwdQlE9cQnso10dizWoo2Ue1LhjFo7H2DLAhg949vKusV/AtqZgwH/yHKkEOtaVvdWuDlIPGkkJ917viml5Fk9n0IXAId8sRHXsOiiOqQcIExOifmvp3JtQ6AB1pAw0Gq0zroh8TA2UTe5Pty0XZHvtW71cHTidIJXqPZIlxx70FE8/mzkdnuTV5WcM20oQKaf1OoEyoRNEkdSG4RP6BMGbFMDsLkfVd6mbnkGX0NzmXDCvIGuEjp4OFXRP3driJQoom0KHwe1xz5nOmEotra2KSv+s/8H2IeiaBuRzeVr4MkW7Zv7Y1hCzTaBmCJkXShTLpNL3TFdWfwVJm6FM3xkxdASXcIUO6nMvbRdXENqlKZW61qkAjuh6xkDzgIkp5aqI0PZnFTt/9ji7FZ8h4B/apG1RwHMfryjEHWo7Kxa3ez6wYz9eyx8ngcoplmciM/KUeibibJoK+Qy2TSCNBQj5t48E+zyHeMmYLD6M4rzM91DC7z7OwOWgms1+vIbawrWMumHNXpd0e5kX346UfsoZreps45ZSkAHJG76QiY1nt3YWW+Gb2byVeRWmdGKuWtVOC+ze53g0niXScoebMWPq9i2EuD+L/16nAhhVeyJcppi/oUC973sj2jdSaXOhkEpy
*/