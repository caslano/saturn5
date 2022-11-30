/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ITERATOR_RANGE_IS_SEGMENTED_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_IS_SEGMENTED_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    template <typename Context>
    struct segmented_iterator;

    namespace extension
    {
        template <typename Tag>
        struct is_segmented_impl;

        // An iterator_range of segmented_iterators is segmented
        template <>
        struct is_segmented_impl<iterator_range_tag>
        {
        private:
            template <typename Iterator>
            struct is_segmented_iterator
              : mpl::false_
            {};

            template <typename Iterator>
            struct is_segmented_iterator<Iterator &>
              : is_segmented_iterator<Iterator>
            {};

            template <typename Iterator>
            struct is_segmented_iterator<Iterator const>
              : is_segmented_iterator<Iterator>
            {};

            template <typename Context>
            struct is_segmented_iterator<segmented_iterator<Context> >
              : mpl::true_
            {};

        public:
            template <typename Sequence>
            struct apply
              : is_segmented_iterator<typename Sequence::begin_type>
            {
                BOOST_MPL_ASSERT_RELATION(
                    is_segmented_iterator<typename Sequence::begin_type>::value
                  , ==
                  , is_segmented_iterator<typename Sequence::end_type>::value);
            };
        };
    }
}}

#endif



/* is_segmented_impl.hpp
Ct4JGq7KmXJ+dHmn7tO16p4g/xfhXbPHc6h7jX4ypASsaWFcIZfltAlfHSPWqydXZJAGIHOkWUdXZouVTBnfdT5BDSdl9LI+6XX8iEkUVZSt0YfTy0N5PLYw8oeGs/bSVI3VQ4yPiIoh6ezpiFWrfzZxpgDIK+fjauht2igYjf5AoOhnrnIl1yFPx2eHQ48mi3Sxdx7SYhMYBBAa7yMEDfrl3fEltwlZBSYam1bLHxh44uuKP2BlFUPNriVNsCerf5bTJSz6BZb6qkt3RPHJ6RRNIcjzuGbrQtGmwe4+7durCMHLPMSKy8o6Hwdab2TBVveuGPtncwbSUqDc4OaPEVGIlzzOrDoJkFaN9Xuo+mPtfDOHVZCXa46JjQX6aKnouVg//qKIkdFYC5IuXCeousbUsFuYCdWaGCZyZG4vCJ09Zg7y7TFbxfcX755oUv40i/TbBJkco68JpzrqZDCHgwhIv+7bZKLnFWv+GL2tHj/MWG5/keVeqDnlsi4AxoVdCjjZjdZXZADC8lmzIaot75aPlJ4ihQwDsYVV5SoqAPaq4eelnkNsdtwUSwhaKTkJg65FyVJQaQc1q+BdhPKC9n2uuLX56b51WFECCnXwGanAySm1y1IK+Vsv5YI+O6uVv2aoGvNnjZtmOivtYz9anDHIptA6H7LU7J+6UGzBMUfdDBvXTDTHGowtUM5f2O1lCil4445aiLGrjxo0V6Zgs1axW1o+ZJlJbdnmKXCsRTPoyqKd/w2GVaHVOocryEWb1LWmbRqxLtqJiSiCPhA8e0GKrlp+rPKuNdteZ98S9A1y8rh4vGycp56WvuT9A3tu3Z+Fmh4NXAQW2zxLVPWeB1vXMroQRDet24/c7nhH8EmqnDaZ3t412YBeU9nexdeXYFvI2xziUckDvMwmY75waSLt1vqdOYZRmNebnB7ZlUOb69k9+ojlp0Y7lKOtB6aUdfxOOYVBxlT5U4CjdqeHpkJl8aPzVSlbWrz/HjNuHl7+ODMeFfI9ORDn8IgvrffTnvlQJqCgoflXUpqBSieF8t2Kc62MK+nE/BwD7B9ls3Pq6IC4PdtaUM7E8viam5rBSxLvZQhh7jDFpTp4HKlnHQk2+jvdtRplpHfFbEecHc7Dv9AE9fKk7kMbZ1SWjKqSKovm42DreeO1dDAmSNKAdyqrH/IaQSyoyqVEF/biqnXrwiBKa95inls14ihfT2LvDt/Nlh1KciSlSqsxQ9QeLRbNvqBYRiHOq5aqV4F0r7a1h9gLca+SmGAJYyGPPdfDRpSQRV/CJAlpzCk1i8ovjQVEkS0GnW4wdSbqn/A+KH3WENzuP3s2MDzKKJAXZt1Sfk/A8n4Qe++uyRniFvWy/JchLGiI/UvvRbVLtZ4EMgCNTOAgcujyjiTnD+6ND9lBpVjhhT0pRb7vsBVelJ8b7v9UfOYge5Qq7zHeHgYU3pTeSk9pEBv7EQQOqjUx3Hkqs8BOL4Cc68TzGSqAn7vkh+Qhjo+It/tmO5sIMiI1zmwZv2jzeyBgn4EoFQvF4/IZMSoEPgFRbGd90UqQVR9zOEXWggV4qIcjdIu6nFnfE5XRRI8NnJkASBVxq+eUXpQkC0V9/fsWYGASF1M81hnCD2UJgoQh/35MvG3m/g8ALYDSfyjxDYRnsJ7VOVm1tO8kRrG6wvazLq3CJKgpDK/dl8Lw0sQVwubnZHViH6UTOG6S2Kz6fafQ9xl81V1me6qTotZp+I3nYLMzI2s3wLRXgaw9FSG1GrX08SI10myuRrH7zMcjYncVid0rK7JROd3WkcbjvaBDrXf4XrGlTsDbmDqxOB2U9sZdLCShnVAWWepS3WwtVhKhBmYfO7uBoNHAo+MaWEenidJtXZINVVa4jG/HcvdgDgz/JmnPKbbv9r2t1TH9O34Kcq6urKW1buuI4G4rHELQuHvx9j0co+mcmClYZRQsoIIHR4os1PtvMIqEjSJZPD5HLVuLH4U96VhEz/6eDcfWxKhUNep33MIj47W6FvjesZG7A3hugH+14+I/sRfxC2trpj7UPWmGzyY59OBi42SmMp+fzGCIHltHCraBTAAufqSgVjqwY4u+IsOJGTX8DHGBAr12wZ8GJ0rRC3y9re24EuoJ7xuwcY5y4QZAULbMyda3ciudfDx6wBsTQJYSPXc1kJpTqLd0CvWWTqHe0qmxekuI+jMLCblgKSrDeXEZS2VBqUQ2tMjXqOtgpcSiEqAm3vDV4n3bQegg0iH728N/i7vsh2pdpRjKGR3QLmCVjg2DwxsGT5ETrFHdBJijQ6g7mfYcVAMEb29Ssq1daeYMu9ItQicKgDbY9bCaTh+qcBUBDWwABgKPsReoFVMEdNhV61qoPmT7YiJuLHaOoeqaHJONIiC8hj1w4uFW/1UHYKpsz0JHzzEBT3IAR1N0YJGr6B3YRJFKwnOt7anXsLDtqdnYjNowxc56Nwwuw6rV2hyH8YKHkFOcgNVBL3SE3NvYsMusDK+yXPuG3L1QBluYkq//YoHNRP2G9moRTm8tcpW+3Y1Dj99MYYVmmPYdxkysHdFpt+0pWNK9+4ZgeO4etcLmsHKPN/T50uy3svajoJkwGfppd7Vx/bTrFuBxGPTN5uqfgGe3FVO4JirABSistaEk39pXF9arZ2dIoa3jxEmOYf72PlyghF0BybYmdYZYlnw6G6xxsF37TmoBZzV8XXEtqfXQ13/CryF3kasQS9y2txgmr7pOX1LKlx7XTdOMUruQGKb2Ji/37GUhua9iEtdtCAEPMsnFbscCp/3tPViHb0vrW1grEDyH+qgjm8Kf0l+UIvQPmo0FttKVjfpOuMa8j+KzrWMaH1EJKkDYUEEvbyScxC0oh1jIG52vE9mkpnehranp9g9Mx9PpuvY+E8BL/5PPoBulBkF7DTi5WJ3+00y630j/M6Y34ZFFWH9xHj9gxwaA+LF1aIsHTP4zV5O2GAPu3MnWOXjiz68mX86wtX7FLjQq3xWNyneFdFguerbXsQLvarzzB54th8JIZJMU5WAp8jGOHGi5WMP2D+5W3pM3muMTWQ/IAMphVBcSafVR6ETlBTShtcTw+ByVFG1rUF/cq6EJUTzCJoJ88O1M9SyPSVrLJrtsCJd6+0cA4snA4+iD3x4Valwg1ED1RYZoWYwMnP7ID+lIYVRnknRSbJyFUzbjoYtpuXtkhq7hLSrPUUbyEuWFKlLb+IbyQpgeJnG9mRTFoU1hpqH5Ra6AKQFYRCF1MOEgplAn6yqqswRgdoAQTmQRkUSPjTeQPMKyySShGmNlFxpSXBFKcfqbt/LyZRLqq7UIpoy/4tZL2WTglp4tGx1/vjF+nE790Vs5d0VNb/U7zKMQOAspZ8L3KKUXfptLYWHBLaOMK71OUljQEAKHre7uVFdyKhvK6JePimInPuSiWGphxlrK12db46YoA1Zbx8Xms0AzBbJTkjkzv8p1AJnTPFZSrUuKn5vpq+HbxcLe5ONgpG/MVtJ6bD+MWiGcFW/HdGUTppjipejZngqqmOBdKt11GWvDCd0z5FuJq7j1AmZ298Vz3X0JUdmR329Vdsh9ZZKF6/HJpnjuQI+ZHN/avxZsFiAi1CkezhLXaoS42KhYDVMDq+zGJopqCUBzZabIwafIZaAocpIm/dOF3Es0XxG2NT8gcGUgYFeGRGw7F9ueyAGyhIswnr2eLm9ZPWqv7uCQ9FoSdrVjB2rPGyuzYweqzxvg69iGOZ69Qdv6nlmX9CCxqJbV8sKRbCobhWUOJbpnXtLNZslqWVH/vzDC93GI/ZJp3PQ9bVwABGUWBtxGLcuf3kAIheM1cLpg9JgAz/tGzwrCeHzU//3MfG4tuyCDry87vgL2AcA9XP1Lrxl7cCB+9cEBwH8yG2LpMfhapnN8pWF70t5NiByJm84iEjNx4WUODSaGm7Mj+vqbCT7I1MNwSiTOm5UCye2kUgEBBlaMEa0q4IuI7vi+QX0W8viPtjXvZBbFGzTLCFayiGcnDeii187WOSMkI1FB9CX+zVGMOBdQIH4O9xHapd3vV3ZZM5lfwpTsdpBE/aazFpRV2SXgMJcgWG9HsN6K+uO3jF1NrPMtgTT8hRH0oUWlbKZVZusgpTC+zmgpKi2S+a5lSotoit+LlOqeO5k4My7OTNyq7Mrvv0XZJWNgJ6xowC/K8ayX8k3j1+9/0WL8oi+1ZqPWcqk1qxrmu5+yCcc6OTE5Q+Mfp0MYw4OxBQQbWuITSfc8YWjGgyAR4eXDGu27gJExWMsCIvKKhaML2SDWDk6sxy/ky2+hhTx/LnJz80BWnRzFTbnIuI8JyMom3DlNpN8V0adeZaLrKb7HBWR1BZqw8F4MlpHmEAhXAQdIzwuuzGQgA9DelouG/WxP3wp8Mo1sMUDnR1fQf37/QLrQrARY31aX6H1sQdbIqQVKXebldu96dKsRl7zr/0J55O/0ETtOX7kgJibhYpe9/4rm5LYONPHypOt8ryQLPccy+wNywyiT1Vi3hJsWrBVl/abD6XRl+xZk9PA+/xDP1695N51GT11SstKTxktP664Iz2ryPwCfXXwYtUxGanuzumn3g5A8AZN5DcfhcQbnIH2Lpdbn9ceWkRGaNA/gF9a7C0zclWLBBuVIDnqMs1q3Aeihv/WcY2orIacFsDyGs1srwsSAPBE1cfvQpIeuaV2ojyEbx4n28WtewjXvpDXvms8dCa4aZ2p8Dj/q7LuCppCtJED6BTF+ixf10hOiuh5lepjVThLOO/GNJUU2RXmOi/gXsF2sHVM3DG5GaT21N5GtPkbFaDdgYZT32cz6fSe96zC5NZvXaaylqEPrfAjQJZK1Lpes5p5wZ07ZAWUBW5tqxh3yKx85DX1xkeMUoAsrEzHUhRzPeQHPC/plprf/A2nt4KGpx5R/nDsDXW3HUY+7gGzx8rp1i3LYgmd8GNwRFqhQrV9SyPEeZyZWQIIYKm2OGqhn3Ai39+1GY7VwVDd5iefXmz4HQZ+u5UFQ+xXd2aJ6UYH1lPrAR+g06KnjE0e2vp+8TAsDIa2u2kao7dQCQXXVbi79FakPLLSOde864r64UmSP0JlOTMYIUJ24atU50HtHrFrvuAzXYpCvxVisad0awMXlh4jpd/nbew0xxkViTEMaUPuggaWz3sajCDyubkfcwOsOwzuqC087UXfBMDa6KM7D0hRwb+9MdocFVCar2H3Y2o0n1OjxCP4VESDOtxgombRbkWUJOWIR/UeXjbJzGgEnEtacnKerl7Sn0F1tnX5vA+cfI4J7ErCLmsALlEnuXhAtC5bjoUwBW4U2Xz7oLr3ns1UN/N2V5DcnqxbAuxkVKWcI7hkmvm+uxjFqwhaqcIYE2U5l+FzuuU4ZvsjW8Qd6OA/GO3wxj2oPPbfiXdJmFBHcm9FaF5YqMIsPFJl5WNKuM569INJh1J8e6GCRLfUY1wMEssGPePB4v0P8DOQpbT2OukbbiEMFoZDNHeUWRlkFQENrrcuJlxwn1U26hXrBHqSHgFBdE67Tqxtxrp1HnyCul3dxNXVxdaaL3bYHNNNXdzHuRFxrB5qL3cPzkyJCjRBIuP1zWRR6INy2l7qetGsPXYddZy2Cu0QrPT1yleKAiZW701b3LrUz00cVH7QVOLpIew+OFTcs2K8+mUtBPoC2P4obk/7jlnT6IM4OkJNK59+WOA5lORbY5f3demfYZvryujM25YpVqFCcz93dPvhq7kgG2mY8uHvkff6hDftzR2Q1vDacp67eBikgTjp7x9j/ECkJSmRctZyM8zlp6vOLdMAOG+TTONFmvkj8IEauLybLn6WiChITykEiarKp6zA5wrbqMTIbElmeulTE31kinu9twGx2j6w8Q9Vxq3zlI7JLRbVZR52h8igCTaNTqkeJYqxFWqHX4B3PIyjMV2cUVlHoR7vn+G3MdCn6jgcuC7hQ6GYnBX5Zh6e+keqaqH7re+n0AZ0Dhh8at786Ahx1BUGNBn1oPQINpomtxabGqfJjaPKRHpAyTUBUn6Sz5ifplDkoen+DxlBA/X6CXn+qtYCzJqxf9m0ik1E9XEx2VXjYnAdVTjCqDDlqIvpnF0EFurE94SlMThwdzNNZCDKHFDkDhWjFZ0nAToWEkIfvpCfR2N7XaXVm5eS3baueNvMdyKBqSMG+g9veNUjGrkC+Emi/Z/lEZhyTUy3f5gAB+cVCsfgoMR/LZVrM+Cgp4oenqevNqBixVf/BcDqNv78/za8ZcDUDRpaMuXiE/cSKZ2ohR3U4VhMh18pXXkyIW8r2sxV4pAqoCRu73cBoFdHVvc13YLmFHTAQ+VxSzlizbiP3N5vH+tzdvv1QYH/q4PJv0XFbx4Pc8WrS4RtaZk8dS2S7+8xIMIGizz56EH0LnC62aatJi9+2dgU/x85XniNPxYmEPhSnbSNf2cR9F4uHstZv4laj6+D3EBB196mDFfx6GH/fHtYXLraZ3oq77G9ldUIRfUuVzTR6RYEtW7coQ8XJvBeK8QY6iudo+tE58KPfB7tnv4BF2NqCbE4M0UPRWrzL4BvFiNCPdG5XBDiWrIuJnRmYLuYnruWit2e7rxu5bsmSsKJqtkJseRty75AxKRNPE3L8sq87MRDT2z7Hu0hhFLu5fhnq7toZ7LbraRVVyp5jyGbBOjsnXKNPuIyzu3fI6BriDinpZHPs1tcierUvyxRAdx6ck7xXan0fuM6Ys1rvvDgLqkG7T6gj1zBQvcPOnqW7gc/j32A79Y7XCXGgQHaU664+hbns2YrRMqYDXyqDudjVoJOVSXuGfFuSN/P4WR4MA+4A+fLZMBHHCx3WT6tRB9AZzmjIvs5C+ZG+gJMbUHJ9+XyuL//T2XSSqPS60kCcEs/hNa3nGFuF9w+N0L4MgLAUcEA8hYlsFR72Gzn6t4wcugBYFR7N2ZnJwbSamH69K8ukxYIwoa6GLBpIZr1iTLcvSdjFbFXpaGXtmcpKqRn/aM4PMzmYxn5ikCwa4Uv44jsdz43pz1RxY9Mx2nMUj7ymDiZ8sYBXbotldbFdXZyvXqkudqiLJXVxkbq4WF1cqi72q4ur1MWF6uIKdXEJmi63kx2oSra+dEgvMRtTaTBdYiYGHwh4wxfFc9VFLki6ODFy8MhNnUFUTtzMYnZW7oRRlP0LH0U2jOpaQDIWcVbX6G4jNYAIOY1VSt4mIZk/ki1lsl2+LYkb53HzYrFXXezq/y7q3gad1u2RGv0flxrFCqGWA17oTjwLxtF/AW/d2gXtd2fKlECZ+2CI3t/gDmbr0A3LUjHxIxZz8M4+lCmM6NnJ5jh4d5ZlkkV0z/EjVDGtdEAnoAvfy2TJmFWNWZnKKjNZdhjEspFB8Fqte6HeSzMlivDj80fqpcGJmcxizBw6k6mZRtXvMjJLMROp4Zhqd2Yy/Zj5ImRy0jDqUoNl1+B1ZlwKx3ST0c6FDLV3gTrE9GNGBY3IPxlpBzJpAkaJ4mlbMmkiqftS2h8yaah0baT9LJMGonGhkaZm0goZTA1PS2TSShiAhKfdkkkrYgAJnjY7k1ZM8YEozZtJK2Uwbp52aSbNP97cBtcH6WWvJf9Y2wb3KO+aAddBMICpV0OiGpLYFPZjQvuTeGR18rxEFvnJVEMym+NUQ3ZAMTTu
*/