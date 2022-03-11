//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXCEPTION_CONTEXT_ERROR_HPP
#define BOOST_COMPUTE_EXCEPTION_CONTEXT_ERROR_HPP

#include <exception>

namespace boost {
namespace compute {

class context;

/// \class context_error
/// \brief A run-time OpenCL context error.
///
/// The context_error exception is thrown when the OpenCL context encounters
/// an error condition. Boost.Compute is notified of these error conditions by
/// registering an error handler when creating context objects (via the
/// \c pfn_notify argument to the \c clCreateContext() function).
///
/// This exception is different than the opencl_error exception which is thrown
/// as a result of error caused when calling a single OpenCL API function.
///
/// \see opencl_error
class context_error : public std::exception
{
public:
    /// Creates a new context error exception object.
    context_error(const context *context,
                  const char *errinfo,
                  const void *private_info,
                  size_t private_info_size) throw()
        : m_context(context),
          m_errinfo(errinfo),
          m_private_info(private_info),
          m_private_info_size(private_info_size)
    {
    }

    /// Destroys the context error object.
    ~context_error() throw()
    {
    }

    /// Returns a string with a description of the error.
    const char* what() const throw()
    {
        return m_errinfo;
    }

    /// Returns a pointer to the context object which generated the error
    /// notification.
    const context* get_context_ptr() const throw()
    {
        return m_context;
    }

    /// Returns a pointer to the private info memory block.
    const void* get_private_info_ptr() const throw()
    {
        return m_private_info;
    }

    /// Returns the size of the private info memory block.
    size_t get_private_info_size() const throw()
    {
        return m_private_info_size;
    }

private:
    const context *m_context;
    const char *m_errinfo;
    const void *m_private_info;
    size_t m_private_info_size;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXCEPTION_CONTEXT_ERROR_HPP

/* context_error.hpp
nBtWJ62/P+pqLoUB7E9T0D+/5QiLEyDnxamqOuBntVmWMpM/GZxznnJveVV+CVzqQa9v0c0ihjg020Y9gp/aO2FdByxIM46B+wbppdV4QqlaIB78fVn+uyzP9HWXZEg9Jc74LFD7FeJLgIsWL5KkBhs8oEltVLfa2Yy95+/NWV6M6UXTjyjKfJYukIG1Nw2NgJmbPGVoUURkniULNgyD2raplwU9Sw1pp7YEobIljrgXXk0C62HQGmPorjQXmLB3npLrFR4gcCYL8IwESEt/tqcgA/ofrJGLnUSQ0pXepEZqmKVrYYH5ReA3d4SiUH2z8yLgyDv31iBoJiiUpLN1xrU8LzdYTKdA/vKpDPpgRCupBC9D+NQc+AIg3gJk8np4coQRrMFkESA0HTKoN11XYh2a9hGeVm7QIVnzpUkbJ3ETqA2diYluCpUPM6BzB5azSW/cibrTXr98caTxsL53Yh3yJUeCWee/hxTejxU/YD2YUZ2PH0pqELOvGExIE/mNViQSyyRfpK5vIl7UPm9gnAitIFuMpFlE+NsE+1Gf75gqhac2Qb2/LoNELeG0RYyYJL0QYExE5GyhGtdwnyJXNBnDdGvRBzJdMjwdyXeXkziAIWIAHwn11xGMqrxRU8g33lRj2gKjlgwhpQhSfoeoHqGAXkxDpnGQED5aDDJ330N9xiraKDj3YMjwNwSWA0TKHLRjotenENaS5DlqIwjsHIiFkfboBeJ4UQxyFD0r0d3X9F/chdzPxutngDpyHf4ccmqBBZqZYJqaQ5mKQ6VHxdkyxcsPYKnWlq/XEExiuMQdwA8wgAonJUxKMtk+eyO/jUw9X05DJnKELoaoj0Fp+Ct70uQRnHUpts5zNFccQGlgSMvwu09JC3lrTza1WDaHglcEb+WDTKaFwgVRZpdeqDp5M8MtVGClj3OPZIuhj81tcXE/UqwFFaImSp91HHef8OZKfIfen4yZDCBMvr8/ga0ACeSGQIAELOyJs4r0cz5K2nni8UiBxA6uA+m25WQ6KGx4FfBiDQz7i2xryEFjgWJLI71nkVac0GzcotIWxRFX8gRHAFOeVFUZaTUJskmoaOQsPZcJZUP/Xck1dDb0XRl5iUuoGDFmaCqn/h1xkiJ5Uf5lMp5lVQ58HfSn+dsMc96CU1vO2b8R4i7FlD6Zmt5rKpYOOEALQ1Lm3IGQ4RYwctP+PTZoCzFkK8usSWRPwDThhICv1I6V6G9hYTcDkg4OkzlqSFPIvofzfP2iAeliTFHqvJoi5WGkIGpmPZ+cM+sbOHhKLahiKp2aU5WzuB8S4U/DRiHRheLAE4WcMAnyPncw5E8sKuWREW5oiMDA/M37EIF00FDrd6unb5thNVM1d33g6RZeR0XawgFwSkuMwvkmT+AMhHi77dQZA2UZBlN4BsqRBWVxU3BhFaEy0jT7YyYJCUVIRJIYTQFsZ2H4GUQQrAdGO2UQR4BrK3GCVzOsvSyqmxAqEapepZyhdWjgXLT0SYgrkT8ZpD/9jaadljpkZl9F3XlmLC1keek15oRld1l5xYWbmbXOPMWdEqGcvPGB06kKvRCzlhg2MsU8zz6hDCTh8lye1VDrfR+zGlh3vRYS5GBBzpDDWmKJDBU3lgqzU4BEeDJjBTTq2gB64OL3P5EMQ0sOC0sVqdbtOdZeTYd8ibSdHrMCXqcIOrkZQmK6LCAJOKQgRG5q6UcqXYAokp5WH5yVmUUyhJ0o0VI850kM3J1/Psvy+h70Tgq1nS9KU4+c2d5h+9T80ES49lNA3DSFHaCgE/GQOS8Q/d62s6SqbEEcr6WoveFiUgbG7j7Epi0meEeGR9zIIHRoqEm4xiRdCbr88gidoStxG3goFRyLHJ3ou5Q+Tl4EwJ+VCYcb2s8whRTyCgiWiISdvUcR6ZpW+wQOLJN2jNitD5Tp1FxOVNg5Z0kQVCWxAebUEiZAPFXkBfTp9H3APL0+sEL7e1mCOXmtpokiaoaS5fRsbQZ2TO2InfOXx7iSE0lTJ3AibShsBkk/os2n6sSinTBkSNDaRijjpsewzR+sqZzr9oui9DnwNzkqWeVj8bXA6deQCDAokKc/3Bng0mF1l9ffxh+z5QRhkHNZiFe/Qyp4XEsTySUQ6VgBBIT4vQRYUVCgpSbD4RZVh1NC6J67eRKJRcO4yHG4iLzdXMd6o0k7K6nVv8tukSCUqJb9tr7GbDfYUxGS+4SCTRloFh1Z800Ucm4W7GMYDXL37sTgA27OV8BEnDoHiXY+z66YyvpU08uep1o9ZCPJ4V6oLJYRppLp7008nJ/Ta+b1ju/Q7rcgfK9LYRt8diNRJm5/qo0K2WBpyHShrQ2RuzwRkNq5TFPkAm2on5zacwNa34fRMMMt0Ae0Rzh+N8w8xpAyMdukYGuVyaCUfhLDjB13u1Jsje9RhyMIY3QlRxJcotY+M1aCZrrcx4aZqsmTc21HgV2CjB6odsgBNniTR6N/tQdlg+ZqNCBdEGoTZZ3llAEZC/yT6etbTxplM1lgw2hRD1t7xD4Gj/tXlqJOaOPTqO1JRKIJHmMUErTkBBASDq8OvsK7OedOEfMn73y8uK+PZv4TNa5GwRYe2BMAySghr1ASnGtdsfVH87u4EfKZEjkOGxzBw/FOSgsDK5vg6O7fBlIB44DMeca+HfIacZshvc11VNrfqEDIbVJk6jzs4pAihJPz1HluK6Br1PFNNpwVBGGJEgEUqADxrLbkOpDtTuPzpxNbrTGZ5hQLDDu5IgOmnDm0wqFon4IpQGTgHqAtMTxkUShAKPSCZ1vr5Yrd8ie+o8EZGXb7BEb0MtXjZouMLgYOdQKZW5TL3uHyCeeSc4TxSuj45I/QahP2D4WNBnPBhwfdIyRmJ4ukOjkELIvYEz29x9PPNeffiKKL0PiW7MF9X+VqskcZqBsg9SHmKyGAnmwrIjhC03gfINAPMkH0w9pOTyr0SqS5hUXxtukthfEc7lF+tlkecqTHqULpIjLkGf53vDnnzzBWhyCT+G0LpVMJSYpJTzwxwNTm46SfXRDDOFpLopTjkUur1oRbQsI2D9bbGMifHXvr+Q2dBu7Si5RNf5JDp+X0Ka9Wt/XJyeqS9ndke0JkOG3OAt5o7j5jbqrupZNmVQ90PsUQ8p1/1fe+rTmlTh6H4gPx1nARn3jk7Yx50zwVutJtdvD40jFwlE4P216Onw1ncDkt8oWkds2BWF8xFKsn9plzCKuzP9wYvv5E9QpJWyhJ16in+n/oE+FyYSIOfaSHdgNRHDlrPZnLOMn7zth3VRKijyzSLBsT7JFizL9ZXadDykdxhf7mbHZ2ZnVtDVMcztCv7BmzoGxAQvS9YN+71vApkNhzrK5q8ACLRwodgSjDKA9YctAwMSzz/NsiXszd55qWUO2uahasmtwASphErKAfUgnRhYr78RL2sChYSmujyUMuaIVc1RCKBdsWaavNY6kc/CdVRpQZKBo4JV/yhyAjQ8v6dq3S+hrwsE2VoGDiPKFK5PSOeZSh9TLbFwshBUY/rhw6kRWq6xWaVN5x4ZYs2q7pFo4ynnTvjnOVahfWJBLWOZyLNfQLog3vzzilfaKoMs5OPpIaT7NEo+IdN4BqLBplmLi9g6iQ6Q02s2IytjU/6vaGvbjaSov5Ycfh23S43isLxylYH6D6G5wqQ6pW6Qy+e4ajbTJjs7AGQ1/e4VAsdke1JV8mvNbq9/aq0bedZUzTP32m9n8h0GdkKQgFHap09+Y+w4d4QaCx+zYY2vhpanuZVBbvjrJ49jcGkEionKK3IDTz1118QdB76yaWXutJvu171LNScPwTMn+xyCUAiIoIBq0hdouKQlEP0xyBxTz4bU2fZtursRENwUv7zYiV1Ww5Mwz8a2mJ0dR7cLVrpfzZm7Rrho1LhkWMMLPN6nLlN33rIXurT7icLz0f/HLZpQh3fr4Ic/CIFcDxRo12nupjBmEtUicscL5rdfenvBkN1StistS9vUq6Q2awsHaHAHcZJyI4KmG3j72HafzmJCRhMOgiQOozdYy4agjupgveRq5lOqh7kA03zPL7yixU14SJuvwyO7wi1i04ot5nztC444QQFiFIOisFIfc5twMwrQTua4soEuivJVUu1kUncPljJzntcZXkq5BGweYjK6DuT/vmojj58WE7rKTbT28rCFR+UWqGFN8rzsWkoF2ZQtTqLrgimfJ9lxlcv/3JLxnKjtbWrxm+rV0wUW7kDfudJGTm2mOSMCn2/ru42RIg40gJQkg4feLvyLkq3s7lST2GnufCs0vVX1cQQwlKkrDI9FJKQJEgOBROs1cnY7EQDCKZKik0kwpryTah/BAZaAYXZI94ck0VaFpdXsDTAlgwhlg09rdQXiczHWpiPrels+Wo1Tr9TgBYgzmduRQessQO33keunQ5xfi8ygVAmwgFDFuuU1oJNCVXjzM+QS+Lca3VaLuYo76Zeq3b7nA+Uo2Ac6vX6f2ws7ypeSLUDweDQ+mz5mQyFIXFJWAXKJWttIqr6eGz7mIx9Zvjx8nHuqvVXKF4GmWMF34dbL+VtC5vg9m4N6vKxsFwZShibQkGcZ2XEWoUvoA3C4GFbRpDoZTwgsVEcpbqmqq0jv6Fv2w2rN4PAgHuV77bxYPxOC5D4k+vp/P12h+7fvWGf31AFfZHRVGYfe+Xs6e3vYJvAEKlPnAQ212tUiYsEFCk5SRU4V1ECoMFo7ZgnIYv11eONQG5cUa6i8wNDMt5fi3nFvLUHseOz/S+Ll8rIyivSJaC3wuAbdPaA8GiifKgjgGCyJ2kICMw0cfJUtgTx0mzky+7qb1sD2ApRZSC4Wiagx0nGds/FmSZJK/GBuJlKsh5XcbykWg2Q8FFCLJi864ylTjxpYYg/HGhh7+nrx9zHsfKTPDAZScqjYhVuwJgCd2P7hVi+rLY5WQYqjEXZTmmlyYpciGZqySk+gLDFX/L/VFTVOZIWVbXz7715yQd68euFMuUkee0H5zGwzjgF0Hkt38zgqH7yROcYeBhLCG+CW2vIIKvGKlcUWZThQpLTexvMkrc/4d52UlXPUXP2ZCjdct5Xl9TX4FLfgySFbh2p//juhpn13uwSTVPacMIFUvHTh6TtjL2wBxEresydwLAcInPDzXzxoM2DoaqrmsvySuI3ZOpMglIJSRd8wiAkhCTQ5x4nE47TtF3wDtJ4zN/0evDfzZqyHRX+GGZ6fW1fkqp+i08Cpa2XCn03EQVoyhIPfiEM88zoGO9UOgNd4CIdn2fprRNAEOkkpa9P4iXcD9wwsNbg8CqJciD4Kb52EGXPqPXTos1xXRn86bnr0M7HDW39T1HYktsLM1qrM6Wti66dZJSMU/JDNilmZUoXc3G2PrtDOiZ8HFW3DDjZsGbnM9y8VDD96ZV1zC7x7ot/viiGFZifLjI5UesRGx5iIIdDPNuTWVYj0v201GCIfHzieGvnKe52SB60O18ddrX2xVXI1syVB7siQ1eAHPW5c60IltLNVWtDw2wbSyBjtgxk/J4p6mX5P3jfpfE+3i5m0lw5oHkMV1SCAz6GiDvJEaQOBBY5mPv0lqIjOrhj75RB8S9dYX80fZChorl5P8Nch8WRUsEImeO4Q0CKaUqmALrD0ookw+e08YcWoqWOS1fnhHUj7JBeBVJkQ4E6NiZlWBuvBOFvsxwRNM1MUqB+YgztP0kEY4Klfz4YC32fczmV+zfbijwPGVzQYT+ZURbhYGWValq9Gb59laV4TzjcDnUA0yMOyxRnlsmxH/bJL+E0NjuMzU9AXjDIsQNbFx4Uxwl8zCMeaSmZyBRQ7wMUk7iPjR7+7tUx8cSKVE/9IR8yGPq/sVR121695IlUxzNdZlMeVMwNCehqLUXwmK9eAy0MogfieGoGhXo6X4fxcz60nJv4QvMnoeENBkRUxbPJd7crAEybqsFnMkMAL10iazEMzlHgYff+1uGLBDBMk54GNmDalQ8EUV5UJBGZiie/h4NPDExhHEykrgbvEHjs24NjbkA9xzu8lY5Z2LMrHfVDAF+7XS1NbFY10RqEZrMuUiDJRXwZQTA06FinA1mERjWuaDk23xiaHLR+QclQm0yRVQPZiFLyLmcuY5qZih0sUk5abmKzULOCWYZFdaFYtiFaiE0BxNkCg6o225j6TcvVoViio3a9zC16PSHMvHmC43mDfUCP45Ko+OKjaFyuW5l9wpr8Uud5Q2NlhzLKth+G73zi+W6neYak2Zbg3sdlUCJkTwHrCtdGF2tAeKWavfjMgO8zdWRP1gN3ilXplSVMyka5cXhy1XGPJ3asx7Yoc7b51hkstqLvNjNxfL25uqbGxnwieV5n1d25rq6GzseKu7ZdLZe3jqrby2tlVA3TiG6rcGZyy3jw9cuKZt6J4ESrWV8ls6/ZLf3NHA6V5cZnc+fVy++r7bvQ916DiPoDB+UFq4f33hUdxq8tOD0XCyvm+ueqfzZae16XXb0k6TZIAuPLL03r/WBA/EbQfS29g2pXwD/dhrCcOEOoPgZuzlzbkMi4PbDjNyFMm0Z9xKvQu7G3IVTyJlgpK05YCqYh2pPGSN5tw0ze9QzdxNoYebijnKtOMfKuu4AZnDHWLH/REUQHpLmxvdkHN/HZnSZUXG1J5cSVSeUEx6RobRPaLW4xGMT6lIL4k0ZYrt6qdvt0+XyTFrt/Mls3jrJIP0x5Yz8kHU8tcLaqD3toPCQcz91irD6WuWG7ZYNo2/FZ/uj3lejKQcn21Ly/e+YtEd+Po28lazmW/EXFLM1ybaV1K+NxXwLN4VOOSk5Q/zlUo3mrxv+C4VO/KU67KdKa40V1E3P5XaFpxp3pEaQxiLvSl+Oe13Ed7s48I7VLg2PhoxsGpJSzbWGVI+mcv0ra1mxhWf755a0bXuHJMlFjSaP5hjfa5ekzS0cmqfW7m0Hj95Nll7il65Z+Vu3QoJd2BC2rr/XDr9+6e48Yb92X2ffBiAQrIM0PHvx/M4tcQgPYOK4+yl6TuyYCA+RVl/TB4mMIn9t7QFzPccEP+TXMnkPaXZfJ+4JnBI0P45ZqP6OHVrYolUSntKv8njqC7imv+udsIO8FDF6XAtPCc/3fV/nMogfSyCILmh9KWWpst0qSYgug6+5S0Nu3GolP8/1uVY7ag2eq3K3y7/jvG8M7jzXNn5KcY42r5/HenT+OlS9doB533xCfukmKztzx/nYhmOaKH4guv/18n7wnqNUYet9l8D0cZTR5j5C9fUn0rFrcVzBa1aW+HF9ku+Eq9ZrIVdgAdjz91Sb5Ofqu05n5/THlayi99Ii31316uelV2354G/i1xYUv+uIuD/KAj0v47uffywpj0GRna+Dvb6PIYZXM3Qk71OrX54STL63mrlv+2n1WxDZvg+OJJ/3sd1uw6DP56Bfb8vTn3/Pc/3ea7nm73/0fu33gvYMPr7A674uZv/szAL+3gI+b5tqFAEETgB3xVZkIda3OHCMOnA01GJw8P/JPUIFoALqwIBg/3KPQHD/zT3C9CwyGgxBJZPJ+t+4R8mvTkbjCf/NPWI2nciSbiyZ/v2/cY8KpZJo9SeayhdL/1fu0fZEc+VqrdH/5B5V6E+2/E/u0Xan58PF9mRr7W6vPwQCsVxb3f5gOAadwVRb/eFoPJlsjhyPcYVSOtRF5VT7Q69BjmgUsXxH0/limWqlwXSHu4oOvdmH650jDMJqm+s/k1Zn6+1uXxACiUJX2/2h3jjSljDf6/iv2QRZxzf+t8fLtUZLX7b4TqFbUJ8pCEqxp/P54Wyx0nD2f3CPchV7ez7fXx/+k3sEAkBT7/n/J/eIsmwvEPFf7hHb9Z9ZsDkWyP/gHu2HEnr8yz3KFEdgOKqb0wunLik7+E/uEfMINZnMArWknjubSZhp7OL1GJmLwBf1UbwYtvVRghTlv9wjzvOjJKV/uUdqGtbH/3KPjlP1PM7/5R7RnKSbpVqfZFiVlJ9k2rWcn/x2GqE5zXJbsT7N9jwpP83xeT4/zfXvWZ5DW4GyOcsPp6w4K4jmvDgrjJegPS9KxnfXLU63qDgvyfK4OC/NC6W9KCtKtbkof88nnSsuc6HYjIEKAS1UqDfAD/ULNs/wLru2X+Cr17Q+X1yqdiHTYdW14ROo108IhFTVTUvQXTctfUkPCK5aRF23bBwMDQnuhiLctB2oFF23bzlslmGDW92jdN4MvDt0ao/bMnX/4b0YFHqHX7oVBJk83fZ9aFwmVMFS/XYagOa6uhtElaS/H8LUtLsfxrWsuh8h/HF1PwoMo/8zRp5m92ecurTqzwR969WfSeZR+ocp9lW7h2nu06qHGf6Xq4dZIRiGxzkxHPvHeSmq6scFOa7rx0UlSYanJTVN+6dlLctqjoo5Tl9Ii1XmaQQ2bIHvz4KUyd1PG3at18+bTqMML1tuq/Yv256n1S87PoIiFmRLLbhNors8uw9ue6EYNa8H0Vw3r4fxkox/j5I1Hf4ep1vW/D3J+nHTXk8Jb2ZKIc8nFIVIxVl9IUQPAGtm94aC/D/jxP4XWel5Mi/3kklKYaLOASExQv8vOLF/ZXWuEi0QjoagVOGZUPL/lJUa2RDut5tHu/9VVpq5ioUKnzL/LatUa61y+/+WFZzBe2urY2XAm0Io+qvHlVSWAAwJ3IciyyAZBAxdML2Si8hEDI5JS7RT48lYLl3YDD+em/V8qbQhZze+u+1ytvaox3eCZ+HZcp7d1O7fHo6b0M69K0RZP5x3RwNwMA1+v7ocziZIairE/3U8Xc63TOvJfhO6HK//BVLU9bze/UXyp+I/ZWUzOfhfsmISBMeq+fovWUFl+ED9l6xEeZTN5oMwNf7FiSXifFPE+w9ZhVJjiKFLW6X/p6xoE7nRwuhHqA+j2SnPCiI4TsoOY/kP3FUjmDkpDeL+Q1ZiwuywGNzp/v8pq3BJROx+MNX/kJUF5Dy1XGa8Qdq/skp4C88/EkRD9PpXVn/304xjaf6V1bpRpm1L+T+ygn4jyZbfoPlXVrw4uZKIAyW/Ixk9geb53CtrQBhu/POSRGIwi/ws8LM5L0gkTtxUnrO7OI75x4ZJwa4PkCkCLTXRPLxYcEgFnU4078Vpjafw0DqayUfQsSDP1Z0iEkhMda4KfPwuDhGZ/gjAs5zKjli3VSBelr7905xW+E0PA7cElKcC0QiyQ7AVLssTqYZApv593Q0=
*/