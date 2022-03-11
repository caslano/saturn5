//
// detail/conditionally_enabled_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CONDITIONALLY_ENABLED_MUTEX_HPP
#define BOOST_ASIO_DETAIL_CONDITIONALLY_ENABLED_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Mutex adapter used to conditionally enable or disable locking.
class conditionally_enabled_mutex
  : private noncopyable
{
public:
  // Helper class to lock and unlock a mutex automatically.
  class scoped_lock
    : private noncopyable
  {
  public:
    // Tag type used to distinguish constructors.
    enum adopt_lock_t { adopt_lock };

    // Constructor adopts a lock that is already held.
    scoped_lock(conditionally_enabled_mutex& m, adopt_lock_t)
      : mutex_(m),
        locked_(m.enabled_)
    {
    }

    // Constructor acquires the lock.
    explicit scoped_lock(conditionally_enabled_mutex& m)
      : mutex_(m)
    {
      if (m.enabled_)
      {
        mutex_.mutex_.lock();
        locked_ = true;
      }
      else
        locked_ = false;
    }

    // Destructor releases the lock.
    ~scoped_lock()
    {
      if (locked_)
        mutex_.mutex_.unlock();
    }

    // Explicitly acquire the lock.
    void lock()
    {
      if (mutex_.enabled_ && !locked_)
      {
        mutex_.mutex_.lock();
        locked_ = true;
      }
    }

    // Explicitly release the lock.
    void unlock()
    {
      if (locked_)
      {
        mutex_.unlock();
        locked_ = false;
      }
    }

    // Test whether the lock is held.
    bool locked() const
    {
      return locked_;
    }

    // Get the underlying mutex.
    boost::asio::detail::mutex& mutex()
    {
      return mutex_.mutex_;
    }

  private:
    friend class conditionally_enabled_event;
    conditionally_enabled_mutex& mutex_;
    bool locked_;
  };

  // Constructor.
  explicit conditionally_enabled_mutex(bool enabled)
    : enabled_(enabled)
  {
  }

  // Destructor.
  ~conditionally_enabled_mutex()
  {
  }

  // Determine whether locking is enabled.
  bool enabled() const
  {
    return enabled_;
  }

  // Lock the mutex.
  void lock()
  {
    if (enabled_)
      mutex_.lock();
  }

  // Unlock the mutex.
  void unlock()
  {
    if (enabled_)
      mutex_.unlock();
  }

private:
  friend class scoped_lock;
  friend class conditionally_enabled_event;
  boost::asio::detail::mutex mutex_;
  const bool enabled_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_CONDITIONALLY_ENABLED_MUTEX_HPP

/* conditionally_enabled_mutex.hpp
C/4Xwi/EX0i/kH+h/EL9hfYL/RfGL8xfWL+wf+H8wv2F9wv/F8Evwl9Ev4h/kfwi/UX2i/wXxS/KX1S/qH/R/KL9RfeL/hfDL8ZfTL+Yf7H8Yv3F9ov9F8cvzl9cv7h/8fzi/cX3i/+XwC/BX0K/hH+J/BL9JfZL/JfEL8lfUr+kf8n8kv0l90v+l8IvxV9/fin9Uv6l8kv1199far/Uf2n80vyl9Uv7l84v3V96v/R/Gfwy/GX0y/iXyS/TX2a/zH9Z/LL8ZfXL+pfNL9tfdr/sfzn8cvzl9Mv5l8sv119uv9x/efzy/OX1y/uXzy+/X//PvUAc5rFxAf9lzc1bkDczfho7+r49yjN0B661CLfWR5qaK7WEryAei6WR54/t3lle9zPqd/Vne/wXZ+q6gPjPykZJYbeht8VEQE5KTqtxg7hRjj6t1ArtgYuH2qhpbz21raqoGgOvxxk9hm1fA4XfigCpA40PNBf2h41Upm1uzh6UsNcnbYY4yQn9WGKg2angj33ZgnYJDJfmvY1i5k1azh6Y8BbaSqH/94eWod87lFo97Zk6530sZFZuP7cPR6xlyY1jN+BFGD6aaFBHRNsYwpwwP5r99pmcth5L88viJjferLf5n5+6EvCb42m8FX9HZ0PW5j9kRrqg6g/s/77HceZ323FxObwF6LopHGT+0EV0YSLRb/qc3IWKauZXuJkVdrPjppf9tXGQcdySdo1mRD0eRk32cur2eQgfE3YSUIhanCKt8JxVefmuC/BmuLxL6JHWSATczj+KZPFonFAQhAfuMAwXxZpy0VygOH+BPjPhYwhZ8+sVeaHP03wLwDDo/XREEQsFCCBEo1HhsWOp9RS/+wBNDiTXeLi5alNcuIY+Q+Pb90W0PrzUD6vGI+X9PjVbozg/EVVjxh/vDWu5P2YaQotNwPs2XErYOx4nfyqgNReHZEEtUSFV4FILPVGD5Fwef5BL7aNndfI2HfzKLeRGhwukvXz19PmHGbuLI7/9I8NyjBXdjF8yT5FzpuBAD5DaAIPNuKLdlTxLal/kGpniZuB2aH7RgaurtVTDTp9yojcNnZUk6Nwp+PH5/mzJd2scZcgf0ijYvshLZfvYTSk+XctLY13voPL0uYIXP/JHn3ydgEnawDezPcKLBh8mMEIUmCi0XtLIaFG0zYGs5i/TsFWeodcpBi58IBzfrcDpIFQnn1PEhff6TbhFDrsA1lZVecmk+orOJWsWMTC1hQgNUGQ1K8sycoGzeEB//RpwuXX7Ha9rHfgfy3rsIGDJkWwbrVRV1XXLq6Aew5SuGY6lar5B7zB9ryvxhMGNAJfZumHKp5ANiw/Ux9NmVZ53/AduMqtUSSTZ6wzwy1TFRlbJRkYN0nwH7i5yXr58F0zifxt+J5X4VkCeT3nrMx8GpPJW1Aag+UewFOW/o5qcnegnlSo3cG+a3s6yDXJxHVlfBpKeoOxYHmMNSSrWH6RungLUTXNxCfInPKaUeTbUIp65OTrImMwZwwns2T9gwVY00E2nGh5KHJgsW6fGBDjXiEVlSjxq5EAWxXucpTAkUUQb+hzsNojhZOgwILo4yb3zRIiUAp1GxQwtzL5d80rCXhlSyei1Ne3orfWA5fhqockfOxVIvRSpluxbBEQF9qcOJtVg8nKOcFyBVvbn4EgExHPxNBqKgPmNSznyI0/DOsfOpyiov9nFuIgkKeTGx+JHCQuOz3h+Otx6NYAvp00OAd1j+ilFCyO/81aJ+eJEjyxh73yUW3yiR03HoHe59dQX8a2VPoRfwJl5wEqYV47hzEckWij0hUNU0/6U+3Y/+jnFRk705oailGsZ1ZmnMPxWVUWLNnJtSUm0E5ep48F/MmabQCGws9olrBjyQRVRYzpwnURBtOMLaQkmWI78ajWqHTnTVw34ls32RKQ4EYfGeUmkF6MPGe5GFFaWcfINYqU+QN3smNceZHJCjnRJHjdBDTeSd5LjwOgNIhVtLTa+g0FzoF93aQNy3RNen8Tc3FJjIe3Ggc+LMji9WKSxT+CvYk2jBzuoQ1V18RRwpms0Ku9rNfg5CnERuCWyyWTkKcfGYeEhzk40hq48M3jAS0pOPhxBUWBbQrhgaepaToBgj6v1KJI07+qtTARthEtHBjPAORhSuSmsCIZl/totTOiXGjt9EfAjMbKR9ewGd7PoFiGGrZ2sMEfiXkzfvcUMxyN2HsAlewkv4jVjlyQDM/S77JhaLR5/1AurCoJjugi5qf0z5ud+jmvRXYeap6wQRinWxJsfyvgBYoM357qJ070nAfK7QhF8KtvWYNonOfMZfDUr7Dj7WVOv5ZcRVLaIW5gZ4ab0nM2AZgRVVvyZs4iPOrK1eExgyx/yTVzfWHz/k/GKMpmFXjJmbKr6DDw++Q5I/nsdwGyj6DGU6NQbBB3JKjFu22iMVl+iBeolsOroC4Re1TuOqjQlUN0lxS7DSGqDyEsEXwXGceMUdrLYima1bVFEWdeUVEpbWoQPLP0oqJAvhJ/EA3XXJPQkTA1+vjiVKxuCFcAZLP/YT3Ih9GuNK6WcHNb9Wb15pXmf2t73BTNrrFMmk+9Ezy8/YEJPCP5nUqEbctcq/2edEgTdLn5E3CBfoq64H5G9PJ2QOcza4fSY/RWxY4bH1taCpxW9h425grY/NzOoXn/kWRcWo19l7dzLWFTJpnk+2GtKqZ3HdttVYL6gfA+BkBPKihKVaQvdZ1Dhku3DNPrEmyKd4dRtxYGAz0Ia8pm0FbuRM6CpnY2on9yeWsKejZev26US1qUSqNidZndRIn5KHpQE92+4BIJx8mZ2xBMaYYKvZZYgghvDnlF55lk3MRKYAA8s8NPh7I+aXBIqlIuvLYvDXHgpjbBC3VyBLPRd3iMh/8wfUCjyKnVAYx26OV9JgF6NuahiHh3zJFB5D19bbkAEJUPcGW1k/snGesoKixEuPpRpD8uYH4vBlDRhz8RyxbvwV9rA5pz4Fh334VUOptAeNnSZ86nAFzN1m1AUe2RHhFX70hg9W5kiJo1sEhVzM/+y5MwYfe0NyL1v8qTDEOOPxOBsAgJxnQNUxhLvAhpthPnsx6raDCcV5xEfreAY9YnKMaKtqJKCGWq7+fOIb44dR2UazDt1xp8x++MqmIDfDWfCsBcWVAsXeHJ6n8t8q7kQ29QYC82XdN3Z5f+a+y0S98dqj7mXFzrxESGV8E216kBBdtg2/B+u9QmHQf36YL23xpP9EycnHDtiz3E82+ieAmEiqrKxoDGT9MsmRm2Fv07Qlz77lyuKrqj0duCznDkWqcYNIWXXMSmGY+eBnurMes5smyq24S0sXCehRqQ1pwWVPSsn4Zo6Bachv/4h+lBsPgF7d7tiRctL8vJR6Vn8ZTrj3e7xE4YEQVRzO/FwBwwzBjGsQUww3h7xG7qIEAwL1nkf+Tn7CAyexkNQQbbaIv/Q4dP8P1j+5xEiYggkHt2wUeSIO1797B+Gf8ANCF/rI4jRb3UCs9G7j4gRr4y2ht/QKBFRdBQlt0GkIEsXsbT37s8Y6q+aflGEFCV3QcZuOiJSp/UwRh98kRrv229feD+8Z/gXAx2jJN6sGyuxHhFRL6Y9eiie5/hERbPAAXqqrmlU6N8RS3I6/cu+0OVgO0pi8AvLn0fKYV4Io4ET2z6+0H1wYJKHOjtaY8jdQIrf2S6QREBnxA0uGG5roQxqRQpFCkb2RQWFY7qeZjVpJ+xTBg/8EwT6nVUVP4RtFuuCMuLWq+hZD0LzAItwG4ulvhefG44h0i/MdjX9t5rsa3aho7ear62CERfiOCx06fBO8sh9QW4/XHvQzTt7K/7ZW3MBHG5aS5Hv+e6j+AhdcDV31ADLbYM/qAI0TDyITi9Z/gt314DIZ4NyO5buMjSPHK4GRtpsn2NlUDsP+T+RECGvqOdAd+RYSRQC6J6MW2Sf4QaRfMoM2jDPPiqDHfDRLz/USFl5g6+xgtHgTBmsVBgQrDN1Jxw/kHMhPIzQGDZRmD+tem5dKw/ut72gWOWTO5vfvrQ4Z/3f2GcHfR2aC9VoSxxF3+FpG5ZACwOXlwJn/XioK7qX/Xhv8P4hG0wXGa/E0HrEE8FRKD9cukGGQkSPrkwPhJYPU8/VbzQ9ArONgRjyQp/Tn5C8/+wYbQMKPtge4Shbir9aWW/Oy1Z4rP7arwxiBMDKf9j+/hIAdtvcQBY/da6AIRnxtF0ruqQWAnSH7qUKB/uOxZQNGS4Jq95oToJEPRJh1XfKg9Za3RaK1BI/4f7eMCvqyZk0vh4Od+ngv3BpRcookj1X4gx9BqrjmzGXPLEX6OhNmc67B7knHCBOPfhWBnFWkn/742Oeh9+kD/UZey3hUbZYF43TnNSJvlfjae6UB6+15i6jvKgtuth+oeE/Iek7FMulrIoGfEXxdemSEpZkCmfQB3jftqq+OxhRdOwK7n6rWl6XkGVq2yZCA5LOUqXzXEnar1SpMfMN2ENbt/BsAutd5s6PvlTSDH2K+qvIZK6Ao5HSfL/Y8JSruTftT3B/+XthTUCFxVbYNjTqvq8flKn+saca0Ie8KcxsnicZ1rZdFLsfBJdSyEaSCNXLsnGiRngyUMjGGYtMxz2sy+X+1gWnQnfXm6a53RVfAzIzFaAy7vsh+LyC7JyV67vh8hJEuxdwNiDEfbXvqKX9FsmqD2Rn7vN9MYDmyAArRwG3JXtFtk+FlEmFrTiEP7+N2va2/v5bUAl31/kBe7YYJND3jrQEvyOOwO+oZz/am/AVWGf93IvwzVnMKpHK/On6IpUXx6vXDbpAiNy6uQxnlA+qbHrDT3brHwQ7JgRZBneMHSpTZPNXPy641ZdUVTK/FxkC0VjFoAbEsxcw+h1iPy9y65oKqsEPrqLw+0QXQeTTJeZnDPcPOOEyePS9v16HwA80YfzNDRwfZl1/sNmjCNoJhrDTYczjGPZz1O5LgN4RvMrik7699tnrFf4aUYoPnsGtQIghyzyAJ8IKUFM8nPka8ILnrm58r6Mj9y7DX6IX1kjG/fUHXptS0agoEZr6FDzc3oICrZVbw2tBbOO4bxpnP+6z2iGupnh48zVOBuIZfgjgBlNbZdgRwBGCKiqzQpeEugeGAsAFgio1M2I+AkQpFgGMoGN460eRT3pIbz02AaI0MwBmCGkErEK9pdf4cfjyGzkIc2gpiohb2Af8IDiURmSf3FAGpPMABRTaOlQJ7+kBCU0GXXZkE1fkROxer6c+xpBsJg/mL3iCT3zgcV/4KfZX78gs+kgQMPmC27/KDDLsHYDqBXk6GAgfGWa6U6j+QXG6lX1KgAOoi7H94nG0I3v0+RGAIAZ5BugMMpAXgHfXem62hG0K33J6wnb1n9FhG2LsBJVAiKnA0eMAg4c91I4QYaZRb0Ah5CD9qCCHt2Bf3Cyy7PejdBFLa3RQFFUfsgTr8ehFd3EVuEHBUWoU8Bewt4mn9q9nC6lra8uQl7Bno3wMZtb4unPyHCw3z5eDayDrJBsgl8T/Pq5x0t9iE48+LQY+Rl9rfgC+WktP+NW/CV4UfhCFOkIjfuQRzkAPO9HD8uniPGUK/tZZf/mRr7X5Tgf1wH/FzvW6rf9IP55QLPSht2cxnmk0dSB74D1cAoeHfNOXFMizqZTybHAZD2Fa/Fi/nhx+uPk2ed7tzoftEleIok74wr6Aw/di5wnjX4k85Qq85Qrc8fvn5EYCIN4Uuf583Ka9xu592fqhU8jmJaiF8SC+yLm9/OBDEF8E9IR9ciO9/UWFnOzddZu6jvu83xX8Dr/CPwnoxI/6kEe4By28jTxTQH/kJbujHm95Fs8d4/A8gvbYl5vPJzvzhDl42k27e55CfzTI/hKW9fUSfpiV0bqTG+0l5B+1nuInBBy1VrYHvM8vYH+RFFmn2JwQNL0QnNUQ5Fuwf7alPwvmGg/N2Nkq9XqRe/vqxF4iHOkjRyG4F8Qs+BQneeXEzNv2Bs8U2gZEJH1lxczb+loE3qK8XGq7TTWq7bca48475WcAe28P4MXvcU+DBtilBS8SdcqYaSe7YWFxe1XQkb7ZiaRD010WWHiPEWS9ZkjVFAQAo8TtAlVaWRkqJHrSZ+xkwPDrnCSvPukEC3W0FK6pz4EHw4AhRP0rtGx7RUeJuwAK/DeHp+ikGMZNsc7AI71JwCCc0EeP8sux7zFo3poGDePoHvJuqs3MDoubKBZVdiuLykQIkJ45NFJ8aJ7UyBG/5sfh5J33ngCJjDFwrVapLeBzF9RX0t/8pmxxh38aN/40iqwH3IjywPjE/i7s54grxzAsU2lUhmLfGM3uToK7o8jq3+KTvKXY0XL+1y7hWl0tKKrnGzoUjGXmNF68e2ofFqD6hFu6qBbPfQydOn+7ZuYjIzKVWzqpFs9EDF1w5gfT12KuP6wQOntpeLjVwYHi13JeSlhuhIMFP/bZQlu77SJ/NwgNSJkoNnN+SKp6/3DhV2jemC78UyAfY5YuwyKux6yr8xl8xZCdRz+A4EYYKvGBCsxatBjsWYnPfip1mX+nXVyaZjD4S999ZS0slO2XFgp7bq7FDoSqQvaH+bBrrHeXsezb2+OxjIXTw8/rh2sDcH0V/5IokQ+fk3zBA0lsWoYm0gYIjz19jVjdN88X7zoQa+X6DsOm6Ld33PDyQgEXC8sf8iAOs6uzpHKLzCjZzEb7+tQz+iSRF1KYPEVtfiLdzT7dkYIAUPX++mcLLyYw+plIiSRocrqILcqS1vySlnwciILIo2g2xIYAd14GuV5LMJ03kz0OAdnnvYf+jp+8SKQlvr7TQ8eh85oN8Jc2Pei8pB/MIUkM4GaxnQTAmacCBkrAU+G/UQ4jbhRF4AhqCVHbSDrKAbN108N+wxhFYgux5HMhXQNaV/0Mf/xi9GxPoivVlMJUBtTSTASBIFBpzj9sMdHMEafvM7P/aM0WbeS15rvrlYYd5FUAgkLsZmGXsVXHyWPzDdT8O2bKQrX8aPR+sMDKRZPUcK8z64ZzBlJu+2DuR+nEedoYd0YHYSTZfHuOdqzsojhr1mFGeG/d8ZKSb3qIkZevstLEceVxwJbRnq05ms6I8/KuXfjCkXsCnYvbmILt9/un/Mc2wAC9sQFTILJ7Igwjom4xa08NUeS1elp/TLVlc6V1M4W/BBejNauA/EgaqlrA6g6ygftdz/WobDb0tCngqMDbRW1VFKQKr+j9mEofZspVxJ7wogQbkT70gEpNj3f2tltV5Gq+KGPFSz5+RqRG2L8LNZchrQVqiEhPY11UU5fAzvvhjzxonIMVPpW9t6NSK3m9JiHoQD8DWbF3khR+I9J9XhAFHmXH4Q+QvT8vh1GMeMQ5RvHi6FUQza7I68vrXhzFzg/HQZYRNxpnhHSUOfKlZdod9kLaT8St3rNQp6brOmJuT5Lbsrhy18Hksl7YGJL4zjDLo9IR4la4vIWcutOGIfZ0FmVvBCkYcIaGyHc3HKyv/LC8w2i2R5NAqAAja1Kr3IPTlIzyy98uSIPmYL5/wW9f6B3KaSbJ5UAYuBnWpINLYSdF8zuNkfjWXvIwYdqF3UGGBl02rlmQ4HbQR9H8ygkB2cABkQ7nr3Oy7FJletQd3yJjkRYec1GPFNQGRqJLQBEOvnWSAWPkPeecCiENWqGdvMbPgh61swgr5YFHm0KPe07ibTBcfbb5xCEpuVyhxbjh7axL0cXRplaHGCqLszx+jGHF0+gSUkv8bopNYMcErI7fFLohT1QLFo9Bbgj2dGny3LdYf8eTh/Lw+p7iqSOow6gDqIswN+7mvCgb/grjXZ5VM/Kz0hBeHU7RK0rJj8fkAdp1bY+OBLfyhzTNOm4+wLqNegOHdyyr0SOnE1iP8lY+e5K3CtabUDEF5rcUC7pJZTgda1HOVYHNgP+BvYsJWhb2MmM6OmMOY6EAHCNagx8DwDTLTmTzB6j0c1JoRXWFL2PthROT2nk7KxF4QCVhzJJmRR5xpQAMd5tm31Pbk9nbTfaLIBPFTJ+4hUPZxgAMwuzqv3aEb9JTYrcQj5JTInwZpwx3ajgSDTI1ynLruuo/mF/Adl2mYqUnFdsNb8+8RtXfimXyNMqmhuI4uZygjD7nLeYNUSrxCeNCwbEE4qMkDSvTNjgKBOMw4B50m+m71EkpZecMopaxi89MUNxJRMVdLjZnME2gPwdMaKmcTdmSdovd3CtcZOEAF744Cu0TbBJsw9vteo2GVEhb9bHE2dzrf7dBE4D/A+oDg9hq5LoK9uFgMUBt7hXoBTAcZAywzgsnYw8s5iyzYaUaWut3qTbeH4uqEHjDYNPSMD+3ttn3GaYc1YbCpbLbhJDBLh/BoC0WNrBNpGiL+u5DZpxzYPItOMctYCUu8R2I8QNhW4Cgzm67fPSUM20yDGTwNvcnt6/1RnzcmYcy0XLolsBOAx0CzifflQBYz9CWZQfBX5eZIosUxa8oIEVYw89vzrfuBCLs2u9DcHFbTOwVdNyPTs9IFng+pNBEXx/eu1S+suUAAwhA+DngkPerucIF/gdyxPOAmviM8jH7fHpRGIY9Xb2Vfq0I8hXkiOqA8mraSqK4ylEINhj2CgFY+ZgZgsQN5YxcAfzCr37kIrxQsZRF/34tSFmF4T54iMoLfwJN5X5P2jRtEoJQYRf7vuLviauu69TKKO9k+pWr1uEFJq+Ss0CiV6j7NiGKzdhswgWQBSZvIjGw/9rjPXkOIzDjci9GnDvwYFyPGtbGCds7m+pDtu2037Qm5OQuoQ/icfydTrvLcPULYaTumBngw4ldxvJnX9VTRPtysPxqpOpfaTpWaQpWaRZUQl2N78imF6f+cUCCkeEEtRd/Ki4/KtA5ZFypHHQtewAJXgCef8BNGusGmCPQRZsAoEAcMJXePKhBGHBQ+/gc7zHBef/4IDFfD5bGEWUnvdunrkrqIHm4gOKLlIPhnseV4XTsy123Ak9DqYBe+Sxml49wDD0/+3bgGfENANwnG2Or40y/Sfs/pef8gPlw7M6kwZz8JAL0pNtDg3439XvPbAgu2CB6gWmBgKGqJ/8YgwT55N61+2Sadw/4GjVB+Nv4bW86tNob9M/upv+IW58FP05MAXz3l6btY3BhVos1xFq1tONI31xC4L3GGqxeDjCYoI3HJgPk8WTSeJcn1zoTIaPokMNfH8yIPX5cvbnbNg09jBm49hscNFE479Km2hM=
*/