///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_HYPERGEOMETRIC_SEPARATED_SERIES_HPP
#define BOOST_MATH_HYPERGEOMETRIC_SEPARATED_SERIES_HPP

  namespace boost { namespace math { namespace detail {

  template <class T, class Policy>
  inline T hypergeometric_1F1_separated_series(const T& a, const T& b, const T& z, const Policy& pol)
  {
    BOOST_MATH_STD_USING

    boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
    const T factor = policies::get_epsilon<T, Policy>();

    T denom = 1, numer = 1;
    T intermediate_result = 1, result = 1;
    T a_pochhammer = a, z_pow = z;
    unsigned N = 0;
    while (--max_iter)
    {
      ++N;
      const T mult = (((b + N) - 1) * N);
      denom *= mult; numer *= mult;
      numer += a_pochhammer * z_pow;

      result = numer / denom;

      if (fabs(factor * result) > fabs(result - intermediate_result))
        break;

      intermediate_result = result;

      a_pochhammer *= (a + N);
      z_pow *= z;
    }

    return result;
  }

  } } } // namespaces

#endif // BOOST_MATH_HYPERGEOMETRIC_SEPARATED_SERIES_HPP

/* hypergeometric_separated_series.hpp
32gpwCU1hpJ5tabnjto3orjxceLt3Ra5xFlpTbidrUayRxoZdBK5P6xqHX864edfPfdIH6DH0KFf1b9ts9540jIt2D5PfaPHbv+9M8zU22fXwlXbbdTnclXbcWTWaVAb4UN9OSGxo3lNQmvF1QERnaL3IYuWGo7mFTMGftcs50EN+tlOgfTqYFr2wGftpfGPPrjS494aPOFdavgI76omNbYDi3d6kbRy8n6P0dCUX9ZuhR/tq7TGHDrWKvIjgSV/YuPc2wz+FDfBsxj+ll/R68/+iC40KP8y+a23pnLOX4EuFHXL8w8/7OQ3i4RPNpVISdF3SQt8rFoGBX5beDzw006APODDj38YYIoQICNkVYQlq/GZINBdfDQPP0TVFG4J3aFqPxrncZUrFCvwjK1VfPIpSgZv77nGZwj3UuuF9nt2l+2Yrpovhf76jGTT/DuWM7H8byujn/oj9tcLkOWlWFYa3VRFAHXEqaNbvdpnR3Thb7OuhOGz6F89Ywd25SomPcNQ72LTuk4bfxxN370JWqgW5I29dNzHrL9NHQ8xTVm196hDoUNQunJFj0h5tfpq0N7ccDlIbVNtlpJWV7vqyMRELEUk3XZlx3ynZye6s8d1C305+cfqvSGfy7MQsBmY+6WQ2j7d6RtXAyuHaa5XiP4BxWF7S9rVvR/wg16GhgeDVtm2vbIONyrtnLkqwCLKdZ2DulawQI9zEi1NOhlKVi8f0NrMyQhuvc/wVc4m72XQuv32xhkurmaUE6VKx3g5MFTGS9Xuosi0SN0uaJClo3ekIMFbeTV9FrPwfkncn+4dkdEg+Mta6aj//nXsvcKpxkRn6iUCQUyE8OsS8ygV3Xe91hTEJftewbShj/7/4NZjJrf6xqx/Iz/wnBTpZnhED8VoVtQjyCuabi5G8iifyRa+mOSCyWkbNYiExrbNej8hSzVFXJHsffGdtoFjStgzAT8JUcpAjLoT2+oJzoR2+bFJ+FIMtqjPRMwvChnhoL0Q7BEWx7iILieTPCXt2o83uZvGmmfNXxo2ar9M/mP24RJna5TlWsASeWhbqKaRQgawh6B3KpGJxnTXipMUJAWapS7ShfDTw3oX1qZnayLzFm9y5yqzdjmqg3YdxTxODTarFXrMfWr7rcud1md7wwu5eC3P0Mid60/FCQoTP//DLihqHiqJWkOM+O0I5WVHsPDPFGZt9Cf64QayqSHFx/rJF34T7Uw1fPdkmwi+gH9gFHnuyUM2kZsjhRoKl+Ek11YOEdiT/U2b3Lr0EKmt2SR5erp9kp6p6/51Yn/+3JZOMyojFiaPyOuebM6of3BNK1TF5s3njWPeTHcKObj7B8rwcnPjbWchy6gGGGt8c1jUDsim+lEkzBvpqzbOqfv6oWz62lKKXKz8kUCG24fm0hRR7CGbcirzwdpS4er2tERO4E6j/UH04S9UPUzFShYyEBoOKhRXOY7BHJkgvdyW0bh6Nzvrm5fsjAAzH18E82oEzOEemB/O0dOf/srZwqksd64UIFThGrWXVRGke/3obL/zbLyRme4T8JnJ4Ks913CmrXC1uRzVO0ux3uStPdJ5GgHmL6pBnhSqx1yiWbDfAV5iMZaad2Y8vtobsDdb2r/mkeMxs228DMRkI4WOgj5xsIW9qo5d7y+8/Ca/hkOyA3WX9OCz+r7vVHBlYV+6QvpxX+96Ty6a+aYGxaVMVGSkn1JWM7SaIVi9SY6dstLRFR8rfDsEhyR2lKwFledRgm7qsudLMWxxXzglkG3SGFsvssKi9sx7VMSQE4b5T38xcUcl4i3cLJZHdlLvfFIQVI9zQJuzLwr7+wXLv8FCcVz+vfE2yf2igC6UwlpKzuYYSWKrt++RkM972QHX3Yury6B5ieD1ky2iHZzk3VeFpldBHcfUkISet0S9+8etM6fI74to2I+Yi5aICHpj/4L8gxgoTnVSTKFQ1bgySTWuAywJ77fibioHQo+jOAQfjztwrs64fHiSqgZ832BIhcYy4WqZRfXlFn/b0DGXR0I7drvNxOaSJ84uETjaVoJOAp+e2y4EwAGxv4YWajfz9Sl6R1++1hr+qZ847fzEbtRAyHVPVcTlcgziWrXWLVdra6tZyHhRIZHTRCMeNgqn/Wm97xgT4uQ/vRR33Ht7QYH48o9qe3Pz7xeYozue3/6xa9XvS/kn5XAJmn21nG+6p75Im1pyOt6E9bASqfr8rjrxm5Q4n9Foaff2hRgDvdMKVm8NAsmHJOQH4rT55lrsgR+Lk4NtT3jBiA01CVMBC5Op2+6faI5eolU85p4C3rAvTvfd8gVk9uFL8fGIRD0w4M6Qjg/fhNlbXmUQaGgHm6dFCnW3EfEd5J9AAjIZMGKe70gxk0CclRQVc/HoW0fNuqR5DhNCMoR9+Uwkps4hZsgaFPwytU3TYcEf5YRXEFdvdEnF3kPNWTrDeGw0r/dbAr66/EOZuYTg14eRKgNwynbNTuHF2R+WcXdhrwukUPG8+bDkHEYsXLoxZuuWSBoo1LQwZSmKDvPuzcTqvFNdzBH4ge6sOF+Lxi+PO48gZXYyfmZGvbd523JqwJzyPAMhc0CclLvn8TsksQLsuONdW4TjMttBP3e9XgUAnWovWA+vfJCeL3c6L5BX69eHxXjqy4DHHnTQ61bIvwJgPTigxy106teNeEgAdK0EIPkNf9gEwZBBiCYSFFPoUCSYBGgqD8oGwwQhb0pIPIFxaY8wnj0A6GcYAQj19+NRyzNXABYoZDFf6OjdswcY6g2jAtBxpCKmcgAgUk3q5xQT9A1MCpiKh5bCPgBvJ6VaptKBbgjO/9mBOSrT9xgCUPxoeJAE+B3DPz5AfHl6XLg6SPrgQKfzTp5fQOs6Te5jBFAGf5aHKPTutgFrIcBh+sNDJxSM/AvY7LYupdaHM53DNrlkBu7cJ5/k2VECHlBF4WDmyEAARCPex1YH2wSvA77g0KLvQa8BPEBU4BXMDlAHVeH13DjTVPWZwAPUzu4GXSH3zoOpw5BLrhCgNJ3mdR6iAIcH+gQeg1+oYRl5Y727T97mKEYAYKdAs0cN0dh8Qhw2rW0z2ZRIbhMEvQAqOfB9YB9CH7TlLIX7CCe5fCsEACjH17C8B/PSa4xXGHK8ZPcLJAS1C/mZDP7+HvB+WbQzZQngAkweaa6gOKBh8cR86ldnSd0AEkSBewDOAhyNdP08F33Yh+2ASALhQwIGVICJhPew+hOAI4F7k+e8jLvexwVgAuRTyxcmtQmdx49xkP5P8JB8DxCoCxITODIExpW4ccZR6LsaxLnMfX7Ek4wIAHkSdAzh3HBJ5Lfn3VxS58PXUWVk4eB8MMVEPEDNTGP44A1cqm+9AJKZj+2bmxKbpY/br7Uo5HsBMGIJ3HNIvLfhTRbAOpcCvsL8N1NyUBEAubo+PgAjbG1KwtbDVp/BLwOyJZuwy7XS19fn/+V9FfLvCW9QSIhgi2s48dACmtxBcglvUuEMTy/a4EHqfXGa3DEXNifjWR7TxEzwBETSJX0murvL8+A9vOlNgSttUFsiANHz/LKz+cx1OgqbgQFEI/UDQKryEtCBTvgK/oEIwO2L1avgD19Anp1LlWBW+EPeCOQR9WfQLRzIuDOvhVc+roNe84K17CRcvsJtNmoChGdaW3cC1ibmVueWXlp+ZT5o+fpi7iYh2QM/UzVJXk/hMUqQWFAg6Ko5T6CJuxTMU7QYFv0HgoVVDQbrgPvMb3bd7sDPONZBwGUezO44xuHs/A78chnp8Ld7sB/Y5NQCOHHsSX5CMjjPlcsWgbO4Xeq39qK76O7F0ENqwbJquIDQL/g9cBxaBLf3RQ+ZeBEUBte6phcQRbk6B+nf3dc+W8PA6g2BINBiXnl9AyAgVecKLBEskWWR9ANAKbhCawAgqluf7eUi+PFC+nMdvLPcdwmJ4cQxfTU3ghuXJ+5aA+YxfTjAK5emKWDLsv/t6+8XDq6vwDU80XbXOmJ4cDucuhXY2ATYKu8GAODKFBk/GUjA9GsBs0hGlm2+eVgD+imrHlG8gG6VoXBUqIy9k04o/PJDPFy4iyUbbvLDKXojOKkcneAy4YEPBZcW/GnuUo5o8fYbTn/XXOejdp4NxmY+0B34Z+1lFc66cXe1Na3xBHBVsbzcANNEsBaqZ/UTvj+vzs5ZgQCnL2Ak75wHwn7hucA8B1BN/mF93wasFS3WA6c0IzDAkvoQntfScr/yeA7B00d6ngLDtGahYcBFDOaLxMU9GBA93Vxch54C22Cn6HP4NOTZytuf8hgCXOcXbvx9mYzYYUh+iacNfMrbmmM7zBgicKG8f8Fy81/zS/+BJv9lc2fmVnfdZRxG7AfavelHCBIFTTYwuy3BceCPPZbP9R5uKBmBF4wA8BUOBxY/7eX9+6I9UpuewyGTv+xhR3w4yT19Q8+eFdRgMfTjzRXxwSI67tNmqFdm94AXiyL7yciTX1sAQhAdW6BkJPeRhk1K7LD6JQYOcgpy3nyvdw9rI9sWHdKUpbYhjXJHaTyMKVm08h1/sz5Bhu7t369qtp8sAwLdTzZykGsj2PMwZGoBiw32scxMZSfZqxg0ywMklBByltsLSvFICzX1omKb99XZjMRv6EJ4MhEl5Syu3xXltZxdSSqP+T6ILn/85PZQMrGVr3lA56J8dICKSK2Y31fni0eF8OdrqYWEFHKCTGM9U6F4NvQUrXEskQvgNOV7l7rkQlrAkEIIxf1imzqAsT8TM4VcMha3OE/sWRtELjOXQtN9touWFboVYvBYARGm25EHp+USlO3ufZgKFgs7uLjirNAEQrF0UX45bx8TEAVuP2/1nH1/nMN9dwf3pzKzdEkJVZq4obl9clhLeQKUg6wSCP82Hecchn2ryl1qJMLIP8EQRUQ+ioGk4ntba5Cw41Ve9EOtkDqNA+TWihF4uaIVTmud+2wz47zIUpGrtubJHrn7PkviN8GLIgbI/zgWAmSCERMkQnADBGxnqGz/+6BQb4YpK8BH2QgF2cOBz0y8L2R0NNAQ5Jj1XSi564jCR5nJN0Z/MesE9Bpl8OPKVAGrQhYpRlxcwQZbPCMTx1iW1Urs5QgS0LXRZGx+dfImkFHf3pvj/Rh2UNVQtMh5dY0eEJRm54+IOtXk0aXonhz9lzw9OIVuk66PTKDaW7lZPgc//LhntAOxWqY60cPMUXLxZ14HLkh6IOefAAcs+NNmrLZEtVZPJXHhxeTIiqmnjMQGDxOioOQlYOmSzIApcMsVysIzA0lWWjTa5P7u1X5MWeMyQPAxbQvKykJgHJuA2iqLW35aCjY6PWa8/pj83FfbRMKBMs9RnwN4J/VdssRiJ0wmAufKNuc+XLH2IuZXHVzrRMip43hGWZ2JBaylLbxTYkCiycjKlbRVcXjAplr6mxnI4d99GcsOXTT8UA9GCSN8ePQwBeNMHaGyZC9aj560+v3bDEcPGtb16l2ebeDhZubf10JzUAF+WBsJUTZEk6IIPwoetnoEmu9EbDRTU1/oKQuvkcWE8P+jJpYyO76UCYaR9NrwewOraQNLI85//9VnSq7ZmZPxpZ7dK3K95Fxp023uAqr3auJNAMGK6FgvblsSUnMdp2uuH58/JBDMew9rfrSG4zuGR8aEVagwnVoBHyZQ5DNmPw3mcz6Q/RDE+PNZgtndLhG/8I29bLls25LmlIMZPj8gNhUr1fN3c8nEw3yHCLKn0nKFu/hRMNLUCttoW5QQX8GzrqeClc4lTsXo9VNnddSxivywLGr3o3S3URHO5Xh4gJyyp8JlgEeqFU59xIyS1MOK5gNzwjHSAQUC4Sb4fMZTRos2yIfzjGHi1LNP9V41Eket455MNEiEtCspK8vW6t4ZOIHv4Yc+AsF9xawA4b1+M1ZOsJ/mRkaJHwlMDpMDezQZUTaZDQYxogTEwkjTqR5Oo5xXsKO05VVxIDJduBj+2KMNRq/4p/j3YMRpNaU/li+ItyLPuz3jUyl5hbsO0O8hmBqXlyn0EMBy5/w1faokqvqHIEFR2ft2qKu+J+LKqthwrKZTOfgdIaoQGYHD5gkc8XlTWV97Lv/OhkU/xN6D/eUIPJRro5VS4EavpSrJsDiKstsbZFDLgNyE4HtZGrJEA3c0k/MhJTPLGNha+ldWdS5x6MV+ddkK34AgoJhYyVQP4WbYSWPPZq/ZWc+6h8Rb/SAXArLZm/A9draZh3P/2Ct4agHqA3wdeKYYITSxTFsy4vrLvkVEQJfQCgQ6OtPQVwLEO/A6nDD5/pL26Vdlbns8fgJqFceBMszfB7HWD84JCNJejLtctgRGvcyahkXbYImXdS/6Gnmxap58IHCfcuJV7VGZjceBI2p2obJjvSEPggN2Agg7IAK7ZqSSAfikSwGY6LIJpvuag+a1yzN6BW/gOS7BRcNGn03jqsxqi4fjqiYByAMm3vEesQBuJ2F12lS4bifqJPEcK6PtiSV90iX4N1BVwUV01OOkfIWU6KLfnbJMfLbF71U4Mr66yAfO8pFo3AP+OlOYyFubPOb5M7lsaj9l6G03W5DcjQQP0H2fGnisxm4pDbDVw4opP7Wk4i/kYj+YK1Fkp6JLgQRmwA9zdGYFGz7XwPAuUp2D86p2zLE0W0wrqtenHsImPNvPUQ+hGS8LpCh3RX9EoVqgWUBGrjGOW5JJ8bIPPjUF9k3EJ3jn+gvPsc7FZ3K+IFrWp0S/deY2fa4ahxK51RpH0e5sRsRnn1QhPpl8AtX8wGQRFBoO31v9S1AFe8uHAWZlRWe2H7F+LCneTCtsnDzOJaiLFi3yIvtNgrPTjOSbi7JTedRIhb1kLzkpqMvgRc8OLibgE/MSRS+fVM20CB70JV3unx2qQ0ZbiQav+8+sp0hqzHp2OPyjRVd8af4cd4QIbp9jGSeP90yyLv/SFlsMlcG8EJnTZfYoX/Tv+Jc8S8SAh7nZLtzBrq1zlh+TUpGfjYsYAkd5bsGKCXpnV/yCw/a0PaHgI/haxO/odq+hisPE2b/SduwqoqBGq7QpdxIchIWti27op9R7fG4mjV0YSm2Isgh81tC4+H80eefyW6+hfI7+Z+iyWwzjPIdgFL1O+g+YqkpDiYXgGCpQS1q+63TAojDiVkeAd7olnAvMEKLo2NZF3kJBKrbNujeltd7sbRqDQZIPIQrhLkKftxKgEjPZQShMrpGHQwVT5eJ0lRIHfYZbgaGBiweztcMpjEFjx8o+VCnAX0mmZLG2DXUK9iycKDQCn0pEbt4NJOck6xYuFTkV906fVXBxWu/GB5U7vULgmh+gXEXQoldDG25ulz9RHXT5K3MxfodpT+SI3HRHcfZ9yMJQcEHm5u+Hsbm0vbPUbqGnylIQBIYYul6kHnkG8Qxx4yyamX+NEDYrgE4QhRZYOw2H2txJkCo/qWV+sTqM9yLYpJCFmrZ8PLqNHEnAmEED5t8SY8X+KAkxkhFuGUlTstb+mVK0EfBkg5npfUZFWKJOVeZHz6dMdqlret+gHTBuXXasNuocRBMfZbNK6bywX5uSxPoUmRdPRyiiTER5zZ05NwhKJcp/Ow7qs1CagK/3UQTEns93CpvrmcjVbCiZkGaS1NEqOWBvptzMyigSgnelBxoFrd2xfhBHeVhWQnExnmSMzK0T5BhQNBxsKfwhfBpWIKjh5tyHDdCOoNNH4YaCj3M1Q7ECJgzRmNV9PvbMiazt6jOPed1SHZOWlXNbDeSaYRhDtXnV95Uaab0VpcNNMELfWhcqIA76rPUDTELt4fhhlSt0ws9Pid8l7M42Wh7upHT3aYc9w2hFqzPbhVj1DvcW6V2KNxLAIUDw6WAB/D/0ee4xOPncCIeEeqTJpkLEWBB72lzgz9GU9pRMG8CMJwakcjAV645kUj+/4+JYG9Elhvfo3/WjLj2cYOn95bDRkOTq1zepMoX5Yky9nw3nDQvzGRaAPHU7qXyfL8/RFYUIE75AgeeoUylWJHjgj7OT3SaRN3WXrW0g4YI+BLzeqmRAWA+2FVQaGv9EQq5B/iTFRGgiEHrPYI4+iygyU0td7yfs1pyzbRI4hik29ZCyk9HFjytJlqFnbQ/GDIyq9EIVTpWxEX1wjZajJkEUW2pM59Z9EGvGE9xTtR2/0unoktF7Wi0008ZXsJAci+nNhssINFA2ybFTSd9IMzfvBvyj3qn1URC7hnQxLSV666IxU5KFZQQwcCYNUE1NvYMotqqHwUHqnCCJwFAkNj7Gea8PwPf++iFNlXEsE7zXl/xhB6Bxu5lifhrwcr+++hhVyhAWe7akmcAjb8yD8xdRK2RGaclEI3cBwvAwSi3+EZxi8yp3cwRmK3i7OalPEI8Q+shO/o/1Y4mvZMHXEGrTIaMq0Dn6Vx3Kth87/ZZzgMIUUHWfXp/45mTQMHXMtAzW8SGCRK6wFNyRe6ZsNfwe1gyTL1h04MjF9Vl9LGgN2WF4qzZzbL9lE/XtP7p6vi348wFZ2A5qZVekG/3wXsb2eOmx3JMRj6mPa7XyRyy14NVCi7LGUQ14/UCr+oAvqTdBBeG9dU5WCPLKcY7z1ldT84JpqsDsVFjlYYX/YYNqwPr4hnBLWagEFMIdsY92ted9tNtt6mehre13sdOs1WeDNQnIStSuZ1gF9nAhLqrU5VeSlGd3OEF3dPo8Yrb3Yk41O7ngzJC0cF3OKEaelmA01rdZxNF4FFFI4eTIKd1MRyEPk1nkSHo6qSccLZH2OlvD54oOGNZURR3pHPaSWSYpgf4MU/cBUn+Lq4s9wBLxiW2X62gzXa8W47lMyekJhsVdk40M4GBwMPEvWdLdX9dYoswZOTBUklRptN0BRXYKoHGfoQOroLmh/vUPEpxy6ALGpsDyGsMk8fYabQZYnCBsLpTe+bh7HnGlA7YuL/QoXHsXc6bpB2NxQ/rgAl3v2b1JnS9lAkXcYbBJ8dgW1tCSpRcgMzVPVsJlDjAmi33JCSbckl8OvdI21p+bytXBZ/NfL1YnlwkNVB2M1iYjdTdRu+68gUbtsqJumpQy7UXI0PoPMARVOAGzbdPqgUEZoSBdaF7SxGoKXUG1sYkcBE2xWzRCjKfEENMGvLiVDC8lXXTcewQa8+dKgc11w47Nb/7NkauN3RilkcS/9w54QmkyuFyXVRAcbqzdeyPh3Tgt6Lyz7A9zFxmL0jjIQtKLWXwUXWXpF9M3/z1Xgs5f6oc/Qjw=
*/