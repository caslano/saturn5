// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_COUNTING_STREAMBUF_HPP
#define BOOST_HISTOGRAM_DETAIL_COUNTING_STREAMBUF_HPP

#include <streambuf>

namespace boost {
namespace histogram {
namespace detail {

// detect how many characters will be printed by formatted output
template <class CharT, class Traits = std::char_traits<CharT>>
struct counting_streambuf : std::basic_streambuf<CharT, Traits> {
  using base_t = std::basic_streambuf<CharT, Traits>;
  using typename base_t::char_type;
  using typename base_t::int_type;

  std::streamsize count = 0;

  std::streamsize xsputn(const char_type* /* s */, std::streamsize n) override {
    count += n;
    return n;
  }

  int_type overflow(int_type ch) override {
    ++count;
    return ch;
  }
};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* counting_streambuf.hpp
RMIdhDohCSmPOuQEYMjRo3L1EMOCm1KmUClYrbSsdQiqDj6G3IqQ+jPcDhsBPc6IvO5T99cJuMVw4NS41P7krSVts4AUfIHYxUraDgznnruA5od9RFnbyVdBV8gyRQvjTwkOMytA6TP79F6CWLJN7g8M9ZuXSAO279fKR4IvpwTz265BGOs/IM4DES06935SDdoFrJcCt7BlW5GilVVMwa4fcp9+e3C35JKAPOUSC8Jmvl5HNqhYRs6Kgqsx55RjCMT7DTW2agQCD0mx4GJNVkhfh5xzqIUO+eW+Fjo4oCL6eQbFHbImXF7GlSOnmiYG4qxeWBtLw2rfUQGlevWqv1ZmELgDBRoJcW/0asvuenH5SGSUjn+bkK12aqz66B9lFiObrdPwdFRTPw6k0iEg5iGHD8iLzYKOMtUvwi/GRlB5wMY6UOuu0Quy0PTHBPeC1DZcVONxGPbTss0vL0bjQqZafew/6vY4W60AYpjAcjwf88r/eJgWQw3JPPKzVAi4xcmQFXjRIR+8sZ9jMffMr2TdIfouELKdvi5x2jwwzIIGbj2BFQsWrTSuVHwFOrFplXXjFOCQSh9kNOISLeAEmcf5mVTsB3I8CyDjaqg9tREAPUKoTaTMfvr8udihdUV8KJa2tbSJeXAck8Ekmmo6CH5oReQBWds6HPzD7BrEwaKXY4P4QFtxuG7p7iLRBTe/0KD7KZ3jSwPmDMcKjeGPBKzWD/qAmXecffnH6IHlBewD78bpc0Qny3RQQIPk4YnLU/wh6b7z3rvlHsblyWFlBps4W8AWWF3mRwhFpYN4nwjFZvbQy3xZSziZagcCxHkU0FauHXM3rmDAQaMy1piDj+eJ7JZC2Sa7fepC2pXeIQUPAPnu6+fnB+gPIADwL5BfoL/AfoH/gvgF+QvqF/QvmF+wv+B+wf9C+IX4C+kX8i+UX6i/0H6h/8L4hfkL6xf2rz+/cH7h/sL7hf+L4BfhL6JfxL9IfpH+IvtF/oviF+Uvql/Uv2h+0f6i+0X/i+EX4y+mX8y/WH6x/mL7xf6L4xfnL65f3L94fvH+4vvF/0vgl+AvoV/Cv0R+if4S+yX+S+KX5C+pX9K/ZH7J/pL7Jf9L4ZfiL6Vfyr9Ufqn+Uvul/kvjl+YvrV/av3R+6f7S+6X/y+CX4S+jX8a/TH6Z/jL7Zf7L4pflL6tf1r9sftn+svtl/8vhl+Mvp1/Ov1x+uf5y++X+y+OX5y+vX96/fH75/vL/9d+7byvKPiIKveU7v5Up7smPYmdK+CHcMM2KuSP7F8KRWSqv9UcVS3M0sGkydsuIL2hbkkY/AYwQl4G3jESNirrBEOTkxP1a4ntPh9zMlGE1QUPapHp5QC3qhYYHSr7n9kaiTosdctKnCALcAJfx3W2tws6H9K+597pnzV0dOVpDz/EVLLz8JVpbJUKO1ccR36Fh233O4X7+PJRgCNTcJVp7NzzrWfySesQ34PZ8HlbSpXDMA7YtabKS52oXznu/GV92XKO97MUI/uJ7U1tuZYa2SCNTktJRle1cYwy5OR1uKYkQ60GeCClyb7SYU85ebbjvAdIp5e5+w34868Lpg0o0/Wb1rgzdKGTxbKFLFvfbrcAq+LADH8cJvMMhTsRTB6cqNJwm6y4g8JLjeBXA69+cY3mRU/b2degsQG0Tn9c338ER/pVDyKmYkyZY71eNEq5Dc10MG4Ing+C8vYsJOYdEM9sXtB7KrezSFNQ++d5ATbW4kKbznxRaPqJJvd7V424O9C7l7YrvCVD2YrC1if5Cvmbd0HLU1jvUcSaWZl/5NBNr8IKzCXu9KKg2/xC4UvWDeR+Xm7m3NqI6Yc+w6WPJr+vvDnjHVUkOrNfXyHbSPTKs/AyVbqnGqxguQ3lcJ3WWXEoeWo538NtKdBLs2lVKsXYHqTKdQmDPhLHwpZNitKv85/pL5IK+MBa/nV20QcDtpBvokH35kjnrUb3cwT8DmZiD8ZA0DblrQS757/MG7GEgFRb80gdY5JX7u9mZ+yZbtM098IFMfkfuuZL0X2uVCyQ+QTBETKrQIhgE7SNOgPgoe1od+mKMr6uj9iXJfuJoBMK9AAlUIILZmcdP4kMiAH+hbNRmIg8I1RifePiEpUaPsShFBRpUtcZ16Yb/GnX00d6h+g7NRNPojt7Sfk8vF1/UVNWLQrqgJjT45TKyKxYzYmHvm/b5cXsBYqxGKwDpMWwP8G5G4XuZpZBPUWb/m4Xa5sg1DSxTYQVEB9EIHN/GSE0RSv/DtS7BMnqXL169LuDgrOV9hhUxx6IMEYWZ/mx/tECOw7qYesGN3IbLL7FIE3PD5+6P8jWP5JJYO0dkPCciteWOayTMTYT7jt6cMLMDAX3vfhZABLl+FOXNibq/w8ODGkZ68HQcXosILqp0YByxW9EtiQbKsXH3AFlMOXYULSRZ/8EKCCqf8fjSIxL+sQYzYzdF1T+DJUf6+DL5rjcckSI4pU0/GC7egjqFAqXNHdp3B4TF0Ge6THGcozpp9aSOb3WD2PwKCv+39R1UaO4uqVZOP4ixeWLam/REgR+HYWeUlZuohDrfs9VKNr1qrm6dX+6WtIXrWyJTYZMlWk5jNHm6X7Yq5MfuYNXzsRfjlgKiYRb1KSrBgccQjQU4SxfDEiSjrHARlzHzA+Drg1rn9I3KHRWXcOzN/WT0sugB5RLcdwt2wFlqSYsG7IjhEZBsQK1Zvh0tSsqhpYLmD502N3+2YpHyH/od0jFfGRUWY4aetTp3hrvDqy6bJJterOEk+XAfaNRrsIIdcMCAY6I0udYIEs5qfaDY6baqd2o9JEY/7qo4cWhJUQ5WXsZ4JXiUVacIw38BsnRsAOeot7VcNEBw21/4rRoHhcR/7W29ypS6UaLyY5H6gOK/1lLIChx8sYOUn4VT0ebLnsSBN38PiPnHSn5PC6D6wDDjaYfNSrcdKK+2Ag6lagXEcxnEZ6jPZxxqaTlz0sPN9FVBSOnQVOfIA347NKZMdBDep9PdOcZyCtmYRPsANGaCgjgxKRkBuOwoHFv0hn7aoWlBZT9fFZj11+w/xLnfwl+k1P1f6owkBaM3eVHsm8G0CIpu6QZCWTDjmLjN+kGfUZjLU2yIUh/GHXkvsUtP/lJGx/BUIvQRyEbwaOlH06Z1onWH4WKa5Ovnnbv8hIOxGycEwrbUoJeC6eI3+Ob+vs2hFTBjuYma7Hb9KwwFZHZ9MI73ISij5XC0tIt8P3xn6bAVubqiEtW2EUZq+uxPUJRZSGBHuTWysQ7SwCSoVk0uXXaq57BKY7jmfIgWzyVnWrsH5Z12UEIKIipcJV5ZZSN7DVQLrYX5Xzug5MCUIN7cU3ES04KfCWcksyPxtHQXfEgWfpptq38txiqA/gK+02JBn+bGK6BRdteEsuPIsBeX0Lu+Snsz7waviwdNpWuJbthQZyw9IJSZb0YFFLjLgjiw++Xgbv4wKJ8C0v5lgFB7tTllC2Eji9UVJPAaiV4lFwEqhHzkVTJ6XlPiJzGjzRS3ewMsB4wtSOeUI7FBmyHZMneXKxDWnZMKv78ahjmU3TJ0f4bs5FH/MgNtEkDN/tzB34xZwTOeXFn2bMujhMfsvbRfg0raORsw3ndt65F/agmAP0EtP23tMLbLwTrOqjhENa9E9Dyu9UoRbU65ppJeyRsK0pBosFoy6TogvFPjhnyF6w0ExCZS2agctlkwhbRmZSfE18XETtzsAnvqrIVj+BtslKx5ganwNwXWmTZ2PfIjNhHUL7KJ5HgqIun+5ly3g8yrVwdUDWiCZ9RRnqWSJwhwL2+aEhhzEvjqXB4melrJk7zW9gKSmIUbaNAklKnWMvhL3mjp2+1VM1E5+kmW8d7zudlJZjYtFWnFKS8qSaU4SYogyk3gGWSHw37hGqdg5kKd6bED6bk2XQUrVdEgvpPUA226d8ZCfPmO+338o+MvqKm2NutRF1ba4mJGaPJVcif/EaAP4tvgH+L7QB3WQLrKaSS8oxFQzm4/W4MTIoWNjIaGp5+7LMj1Sd11a8qfROJ6LTmz8SDeJmjUkOVTsu1sAJck0nB3fXM576yjZe0Bgxt65mMVnRn3zyCPsNmKRoqAGl6beZyHzYQchgBGS5q4z/ymohth29yWlGcIpBB7jvAENYeMdxqx2T2epcpZmR+MNGJ45eQCT/bP1zsYIUvP6+93mGGBM/mR5rCespt5dGiTRuBO4jM6Bw+hOFDWMZIIMhmlgnmnTa7mh6SaTHJwv/miOLzrtHjKeGF08ZhEiD+vaVRdrfNWwR2ghkRtgPnTkWjf1cb0jNC6KI4Nhd8qO6XniS0CN5eXdmv1LngVuZ8fELomXh3g1wLm1IWlpVspE4NVGz2iS+AdqQKHj8iWxYgRTQrxpu9v7wxb1oIoVguR+rQs9MBix9znKZwhrEq3PWBMbAFvbWc0+g3DhQFki737VKAHK0/DCSNqK01qOPCekv4uQWEzHPfdJMD7OkI3+WEhyOXPiIZEr0SZvUovgwkIrEP3uQ0yAquWSVszh3O6ziOgsjE0cgKxhnlYIl6L/Hz0eTiLozge/m9FqizrJxoDvKxirGVloBFNY21acwMsUGi8IV7WkPqeOKBwvdLT8tWxrnnaww94KbPzdBwFD8/IyjLQNGatJpoPDX3YOojtw/hK6qLEXL70vG1GqAU/S1OsgkHuG3Nka55mIJ2kF+U3G60w2K5LLw4+Cq7ACnA6ZrM2CrYULttxv6WkVsi5ku7WtZvu8juieWho7XEy2Mka0APpD79zW6fDSQRJ/AoYNC3onc03KIwMXMPUPFt7pYaqS9cs5MLVtWHDdAtYMbrui5W5j02muCNhiJGUUAHQK9VuneWLH7FYI3gkdkd+27C5TI1eDzLnHiadscGiPdqMI+rCo01kqxL9bpdcO+UdIQSVgUvZzfY6N6HnsOOpCPQFGSfKNJNDz+abjadsKgyHXJrh5u0sOABGxgXCBc8/p8N2V1gH53KtM4B+M4wmlP5P+HMKR0TuERM9q1wL7lnwf0Rjie2Azb6MdFtj273PkdqL4byIJjDetszkNzJPAWqmwR2JCnLhhYOlB9YxAJVx6qi1R8Dp2q/vH9my5+mJwut7hYufLGn7wywofgrWnk7mtc3hxhddQwydfKasz3u+ZhnYyGLsTlV20kY+RQblCxTQAR8f9V0jucHWYW6wPf6pHOlZE90N5h4308/yzh3FOj30BPcwtK4NqEbvC+jsbzWobwt/z88lotPlSxbQdQNo4f4y/GjvCa+sytc/uHhyuDseGPTcobJuqBMc2o211jAS7qGfoD9Qjxr0B1ZFz561jgxl6Nc/cg68556n7YFnU7mGYE/cOAH1EanVNQEjwW3MC0B69ex86hFi7INktqZEh0p9svC/vb29EhtzcquwwWCvW4hUNY1DuDu8pBH3pplMgvy5G/oj+upOtHhd2tz9zZfIJEkDZcDV3hlxARPRlTOAA0e6ro39txLcH8BfSOr3qPHjpyiP+ZZGC2+8klmijOnQBVPInlmmhIqvEwtlol1gO82SeoyD4ahXInwReBf6gRc098J8pU7Q1yEdkGKdUXKa8CT2VI2uU1nkPGZsK0CvudrJgTVQCm7fQBmR7vlus+uEXdJFOZiMn4IJXnLrGwX1c046OzkQCsp1p0lfsiEl5rPHtX/iLlnzVoExdN5N/w92Rq7UJ3PyZqcuw8RTjqDknEKGibr8XZZfDKzv67oiti1iOMd5NTcLuC/dW0ZPLGmyrMAE0a8zVaNQJz+aiufiz4ByDBTxl6zIjWBYkSNGtJr9DeopWFzQRQfGmDdCtuKAdr7ERkCQRZnRRAkfkQSuZ20McOhkiNhtrNKmQQkk8BeNxThkkl/REcrcIWo4a9IaNsyGkFAZ/ZAU1ru308BJiqbxGXREqNBojlXoH3/074ucrynSH2sq320NfR0vYwJAMxKE8ywWLc+MXhHnCQfsao3Z6zJrkCMLDNGGdNol0IYc1nTmZ59AtUWvvts6/XAbdIxS6/cqJTG48fDDJrMuQ17uk5VCqNGAdGEJXcbt9cePKCTXMmbT5tLG6kzFFpN8avsMmA+y/tGaOmzd3tlZIQKU/hsPwEaZ4LEfYxT9h0UKj0jj5PGp7zCAGOq9Tfl7jRhkfJObzLnDJEveJKhJ/bc51NjG21o7g5KgK51BVsbJH6Teiz1Remwoe6QQJ82uMiSK2e2IIKS8ZaeS73Vmq4PbsvONcPkS/mkyrtxMjjPQoHVOCUEbmBauGGm8d7BLOIhia+XrNym2eRWcHxnVxvtsvrzPUCwH+AzInvFk0nU/jhv+H++L3FWjyEH+XTfRWVjnxny9BXyfU3Zdreg1fQ86NDYpVnvSf4iNi7ZtgGZaqcKLch/DyxBhQ+52lbL3qE02TbkMqp0wL8JID2+moDWGK/1hsJ40koRliE7yrghdRKmwdhD2zFU1yP9E5/ZWcFt2oFWrw0FlKyFISzWtkHJY1SACC78XatC4+ndnxci+90PHTg1eN2G592LZ+eqbgnXNjp12fJ6ehvWM9mRH4IgmWGrnQv41JuCs38bipcbpKH4l6QKhId1E11QcG4P6oh5kHL5O6wzphQ4fo4V+IHOp2Fk7/6nDVFbg1VOQRNtwl0y/hweZQXjaRiLklKRBiAe6WbrFL8TWKsTgLOAMjhEsDGmTFICBRmSlsQf4CnljZ825vZ8DGUtsEMi+f8Fl3qjP6/VHO64MXtIIeNj5tI1IYXuoI7wUdFQsdZWOhi0ZexbzWx8doCAzwH/Fan5Sz85C3T5VkHle52HGWksA213uivqOJeTgs0by+dkjCJwTTxHYycDQaLOJZQ9T3OhrBtxi90nlk/hjs5OBBevOdTFL2KG9pKb8pGCDNFfZpnmmYWfC2CHV340HwcJglQKfvjjcw1Ux9nFdBtx0o+q2ypZFP5qjcvcO/NfqB+v1dNaljlnW2lBFKdMaYcxkWHz4C5nE2eRtKgb00OBS+YpmwHTsHrG2y8Avxnxk1dELr1iHXUvs21fWDVQ8lXYrJ0tZZgT8AWIRFHMNphT4+tR6WLGJEv0NCbZWzFWJEowBAf4jOA3mUCqdvL3gqXy30Ci9OQY37B34GReZlf9l7hM8luGLPBqOMTWbAq7MdblE3WlnqD+6/VreGYHwibJUIE8E7+7eyXEALGooM8Qo7gmirETLCbCs0ApaknyRQi+w1He+Khu+abdCsZ3Pu7+chhBOR0b2KkPRObjU7OQuyyXl/S+So7WeN1zvlZIra2E6M2f/l+sOldxhya2IWTczkOCjJPo1IFFtN5rSRl6FwWIcaPAapSMStlfCJpcp9owfpa2XhUS/fj0TFtMm6VTX1NIrJcV2lrxxkGrWSt0fGFMV55WAyE6H5FJdoqSUF8Tu1K+kjFwUBJO5jYohMhJ5lhwbfs+f2xZulcF6yjXBPK4P9bCdrCLmEkTD3p5ifs2xtrodtpcZzZzBCKJVJhjPr/8DIYDef51ckC2hOyPUBz2kWpxDbJmJ0tedyIQC12FcZ34+AeYa46I5WM961ZFIrXC3NWx9SEnar4y+wBEG4syFmD9srSmgERDRjX7qWBEqVzRbg8bDGk7rNPg1j637/3QL+/VXC7AzsvH4N9GNSJyLPyZqEMX09NqJZCsFMjc7tOqfmawpyV+haahQtzqXkZAuJS2KIZjJrl9/QyJtXHwfHwNWyKHFAvOSWywwPdNAh+G6+2AFTokwnbk/camSIfh9H3vacM3klimUEsNiyOxdoooIUCMkOz4SzS+l7QmUa6QWoTS1jESWpLNX8c9s1XbaxtcVFLZdV5tpkH25lWfExp1YpFvV6p1EiwQ9B5nHoVVQvyLLbIRRs/9XdSSxbPIHW1rlbYF99d65wIr/Zn+G6PHslP6h8X8cuJboHtTRR8n2Wv1doQcseLLylRCvTHmDwRhCJEF8CV1+HQvL+rBVDtqTs6A00ZXNOZ6zcVPMbKGkgC9nSPIDkYovcnjMbvea59oYsuPjzJJnyr2mE6r564tE+AAaIO8DRvcLPx6q+CgNhee8sfN4jKLean+QKS3zKKlfJXfehwnygdsfYFMZLaYyuchqe0N/qs7z7Fcx/q4U5HxaRVDsPlckkHMLX/GJ0xsR7PBLJXHaDFDmdGgvw63H7COp2RQDV8xnNdo3jZAZcbIaMN2abFzN/B8yTXYcVm6bhJagh7I3iVy6RtsnygWUlq1L9cxShGNEZquRcdihdCxzf5Q4+tVn4SyVgkgXRimhyrXm1vQIG7xU3IwKRzgtmT6MBx19tuXoSeALZ12//Hevz20zhMwqWN1ikvBlyxFvPYbea37uq4Hh4yWm1X+oJyw1FRF8zQe+JkQTpYAHliu+S29m2p25kO+Hj1uYmX5LnAhuJua9ArUNHyqebZ3fYQE4Z7IiRzGApqECWOrpo9FM19+zd3JDilTYwGpSR1K2v18vGOvQj9VcdiLXcPVIbdlWVa1RTBkvvxsJ7n89vpN6lI1Uz8wAL6LKvA0N2dPXvhSDzdoXQ51eAyFZFOaeJL7WYcA6MsSjZpknBnDN5Sw68XZwdlDq0IuraM6sfCs/WqiSQpLPNimrbcnr+fPc++oFb6sYs6sNESJU2os8uMxkFBoyr7n5Sg+g36iTPt9SkcCjydAbGo9yzJlTjlwvNzv9VIQ0DqlJUc71plk4W8KLo31l5O28B5sCAEyv3gbq2+XhUKIc2PSUFJarGDs6sa3Hf22fmx3+h2M9rhQAwL9orthAHYAplO1rCGa5INP5Bwkav21Tg3EfcDKRfc+bl3dtWBYfKWs16xQ++tizwRWSx2gFhplYXdcieyYpt8kvAGUuvnJry/E0CukhYXjdca06Muhs47nfdzqalSPqYyt6O/vERcT4YiqS46XIkYBMiScZiVZswuIJwNNfkHiUGU1Grr+tGBOOnLR9azae1kN9A21WE/ZybPnWCuE6Pbj77RpjpfNdbtdF1SKij4Z1+h2UKE6BPDZuJtWbhozlfCZLCY3yskU92WiL4/KEWL5AzNTxQUO7Z7/ASygAMshbhpiW1hcTrmAZBuBYbpNBU7f95y1rabwuFsqaqXNLv3UUiLuXJQmLNpTLxcFepRbRPLRwJTlpeY6L2FGrYV1O4eP80j4WDusbEmun6O2bkdXJumYfNY/T5ASOAe22suw=
*/