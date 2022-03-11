//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CONTAINER_MAPPED_VIEW_HPP
#define BOOST_COMPUTE_CONTAINER_MAPPED_VIEW_HPP

#include <cstddef>
#include <exception>

#include <boost/config.hpp>
#include <boost/throw_exception.hpp>

#include <boost/compute/buffer.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>

namespace boost {
namespace compute {

/// \class mapped_view
/// \brief A mapped view of host memory.
///
/// The mapped_view class simplifies mapping host-memory to a compute
/// device. This allows for host-allocated memory to be used with the
/// Boost.Compute algorithms.
///
/// The following example shows how to map a simple C-array containing
/// data on the host to the device and run the reduce() algorithm to
/// calculate the sum:
///
/// \snippet test/test_mapped_view.cpp reduce
///
/// \see buffer
template<class T>
class mapped_view
{
public:
    typedef T value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef buffer_iterator<T> iterator;
    typedef buffer_iterator<T> const_iterator;

    /// Creates a null mapped_view object.
    mapped_view()
    {
        m_mapped_ptr = 0;
    }

    /// Creates a mapped_view for \p host_ptr with \p n elements. After
    /// constructing a mapped_view the data is available for use by a
    /// compute device. Use the \p unmap() method to make the updated data
    /// available to the host.
    mapped_view(T *host_ptr,
                size_type n,
                const context &context = system::default_context())
        : m_buffer(_make_mapped_buffer(host_ptr, n, context))
    {
        m_mapped_ptr = 0;
    }

    /// Creates a read-only mapped_view for \p host_ptr with \p n elements.
    /// After constructing a mapped_view the data is available for use by a
    /// compute device. Use the \p unmap() method to make the updated data
    /// available to the host.
    mapped_view(const T *host_ptr,
                size_type n,
                const context &context = system::default_context())
        : m_buffer(_make_mapped_buffer(host_ptr, n, context))
    {
        m_mapped_ptr = 0;
    }

    /// Creates a copy of \p other.
    mapped_view(const mapped_view<T> &other)
        : m_buffer(other.m_buffer)
    {
        m_mapped_ptr = 0;
    }

    /// Copies the mapped buffer from \p other.
    mapped_view<T>& operator=(const mapped_view<T> &other)
    {
        if(this != &other){
            m_buffer = other.m_buffer;
            m_mapped_ptr = 0;
        }

        return *this;
    }

    /// Destroys the mapped_view object.
    ~mapped_view()
    {
    }

    /// Returns an iterator to the first element in the mapped_view.
    iterator begin()
    {
        return ::boost::compute::make_buffer_iterator<T>(m_buffer, 0);
    }

    /// Returns a const_iterator to the first element in the mapped_view.
    const_iterator begin() const
    {
        return ::boost::compute::make_buffer_iterator<T>(m_buffer, 0);
    }

    /// Returns a const_iterator to the first element in the mapped_view.
    const_iterator cbegin() const
    {
        return begin();
    }

    /// Returns an iterator to one past the last element in the mapped_view.
    iterator end()
    {
        return ::boost::compute::make_buffer_iterator<T>(m_buffer, size());
    }

    /// Returns a const_iterator to one past the last element in the mapped_view.
    const_iterator end() const
    {
        return ::boost::compute::make_buffer_iterator<T>(m_buffer, size());
    }

    /// Returns a const_iterator to one past the last element in the mapped_view.
    const_iterator cend() const
    {
        return end();
    }

    /// Returns the number of elements in the mapped_view.
    size_type size() const
    {
        return m_buffer.size() / sizeof(T);
    }

    /// Returns the host data pointer.
    T* get_host_ptr()
    {
        return static_cast<T *>(m_buffer.get_info<void *>(CL_MEM_HOST_PTR));
    }

    /// Returns the host data pointer.
    const T* get_host_ptr() const
    {
        return static_cast<T *>(m_buffer.get_info<void *>(CL_MEM_HOST_PTR));
    }

    /// Resizes the mapped_view to \p size elements.
    void resize(size_type size)
    {
        T *old_ptr = get_host_ptr();

        m_buffer = _make_mapped_buffer(old_ptr, size, m_buffer.get_context());
    }

    /// Returns \c true if the mapped_view is empty.
    bool empty() const
    {
        return size() == 0;
    }

    /// Returns the mapped buffer.
    const buffer& get_buffer() const
    {
        return m_buffer;
    }

    /// Maps the buffer into the host address space.
    ///
    /// \see_opencl_ref{clEnqueueMapBuffer}
    void map(cl_map_flags flags, command_queue &queue)
    {
        BOOST_ASSERT(m_mapped_ptr == 0);

        m_mapped_ptr = queue.enqueue_map_buffer(
            m_buffer, flags, 0, m_buffer.size()
        );
    }

    /// Maps the buffer into the host address space for reading and writing.
    ///
    /// Equivalent to:
    /// \code
    /// map(CL_MAP_READ | CL_MAP_WRITE, queue);
    /// \endcode
    void map(command_queue &queue)
    {
        map(CL_MAP_READ | CL_MAP_WRITE, queue);
    }

    /// Unmaps the buffer from the host address space.
    ///
    /// \see_opencl_ref{clEnqueueUnmapMemObject}
    void unmap(command_queue &queue)
    {
        BOOST_ASSERT(m_mapped_ptr != 0);

        queue.enqueue_unmap_buffer(m_buffer, m_mapped_ptr);

        m_mapped_ptr = 0;
    }

private:
    /// \internal_
    static buffer _make_mapped_buffer(T *host_ptr,
                                      size_t n,
                                      const context &context)
    {
        return buffer(
            context,
            n * sizeof(T),
            buffer::read_write | buffer::use_host_ptr,
            host_ptr
        );
    }

    /// \internal_
    static buffer _make_mapped_buffer(const T *host_ptr,
                                      size_t n,
                                      const context &context)
    {
        return buffer(
            context,
            n * sizeof(T),
            buffer::read_only | buffer::use_host_ptr,
            const_cast<void *>(static_cast<const void *>(host_ptr))
        );
    }

private:
    buffer m_buffer;
    void *m_mapped_ptr;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CONTAINER_MAPPED_VIEW_HPP

/* mapped_view.hpp
D3ym5P0o4n1wpWkEzdWrjx0ZrJTNe/08+SlJVMyKaBcnhX7ILlXZrH30bHC9Bss4m7ynDER72lKQ9ERivSgp9TSw9qv4WfFKfvBLDXhoavtpu9TtHFt9tr2frv6fx/QTIKIvAzwJ/eaDCViUf6LNdLRkYsDHEItueaYXb4Jwv4B8KTUUTHmIgsEZmAA9P+MPfsTEZvBBGfRTvl1g9+4F6/EKnQmB2mHCH2KBtcSgGcgKxN0L4sqo7HPCoLHpMXLcjlU4MYJcQwvyypTJ/rWL+f3qyHHrT+iHpZaN5fIt/jAso+XqAhhUENWcFN8abIrNwheYY33ArO0ZwaTfFzolOmMDO6hiMTStWhsjKqnDWN4zoD6fxZVHh1YZ1ksqCwnH3nt7tP+bQY4rZo3N5jgAl6byi6F6YH+VDZniWtYcPSpbb5PDvNu3IajmS13n7myiT/WhUY0vNKgmm3HYZcZcLURn1PsydjkQ7xgFuCUSNQjLnF3J+xXpjetDaq8dAA92hIbx68QgecVOz6pK8JbAcIv4mqD5XYh9sJ2iLoXDGKafWpn6QYfxOFfAqxvfmEX7q0qrkKzqSZvja3YLldTblwCfCfjfLpu5xqTppRMPCeP1o3uzVgVg9CrK879vcXCnuORIx3kPQDWoLOOyrAGdANSENT/g2C9nAnrUgiang81d7OshmxIouC/pxODOP8vPi1Cjvwya+liS9wUaybjMt9LSpGoyMeSFG0GIAeLwakexsgppSWYNI6bEo3EbwUvX1z+fGXCzyx2Zl/23TqT410g4XCNtO30Oz7gVb/iuhw4whIFwjQtfYD/oMcufVAg4iolvj6tW2/havJRi2NP895mjBMRGL0rZ4acm7azQQFNwhwsvj683os61gyU0yklvTrQDqRJlG6Plgdhpe3KTMRzDHrtpv4PZQNalH0tMH7zgmAKBMmiKTX2We+ttGTXaHLE692pT8cUIR4I5glD68mTnvzEivJbdpp7YpHXIfQzeVdERNyYKQ4ykP/e9vRo5y8eYull8HnkPzEYaerguM4hfaJ89QDRQdtqsBJStJT9bcPCdlgL4oFMF5xheQrzpRC5Zx78c2uV7p9YXd9gUff/6rdLQ4sq/MbhhzzvTm6pfPv35iphspnAjad8ksUt7X+srvfWfynuj562y1TlvEd6SZJB9Q0lnkwPgvbLqk/ak4i2HEq9yJIQWGGJiFR3J3YeofyamUzvR3mQap8xJKLx/NNI0cg2i4TWC4I2V+WpRRVslqVw1LYBgCT61b34aKm/RqnLz2heeIe0JeaQBo4ipvMs+W726MupJjptcWa6gdRM/Oq5fdpB8/dsBqI/x9oBEMvI3+e+ngpScATIDor7pquEsiuBLbzATp7zGtIU2EtZCb/2nNCqe/GEbDOGVJ50boS8+pLvG9VXeysRXEBbawPanwebSaD0p9/RVvO2yqA7TcngdXxlqG98T3+4KAvr2Fh5qHMeQTRmnX46UDcBjT0t8Uk/uGkQcuFpRLpBcwkBH2VnSya0wanuai6GnQf/q9D8dg7DO804RGDHH3U4v6tYWR5Wy5Wm2JFuebxz5j0crq/sAOSMfNKgp3F0tUwXNOcjJCy0GV6cwy3/Lc3RxGMfapPnOZqqzik3rFzq1jx1Md3LAILxVogNYWc93etiV3JALgDeQxWaAClmXsfet35Gz/CPUx3V9tvwQ9dC+G4ND21KohQF29Pze0elQgYcTQSWUNbtjh6pz7oaT1vbXY+7Su3v/NXe3L9pKrs5WtAKlriKH6e/jIIYgJAMdrAAOLGcYBY2yzWWaekSOYVg72UjySVi6JYKBRvj3Q5gAm93744Ur33oH++AiblrxWo83hsYSrGLl7mHD2whMvliqs37D2fARPfzjK9dSsAt+pnsJCyHaFb9MkZUD1sV8HJ/km1KrTjeQfXFkk4/3gb1YaApZKIVxru0takvfVLnFdbTMnXtaztqn3LSAGFniEFk3ezETLk7HyrvCp+LQrWFTyQ1Yb6iNZc/DZqtn2uv5F8pzjSOVWQ5n1Uma22ZDH3yR6Kub7uqcuaNr2tQI7ivBe55LgfsZbHg6GbtuLXmc5I3n8FsTRnCZOZat9U6vABRn4Gp10/MqJkogEmCGod2K2/GFBCn4St/zEOY3m5/33jv/9CjchQNzFRKj68FLrtQztIT3duTIL0Qda589ndDFR7CSPMP5umERptFYB/gSx4bnuNrzMculavtgnNxaVBeD6fWYrlqeq6XGGNK7FhI/++FPSjbcGp+P2X5HxPRob3FjbfKeNiThk9bCsCxWI0yt7fI6t1aOLDb0DybsJBQpGzyVfbzkpdVUre3gv5Kcc0v9LpS2rZC1XuUmpy5ZcBOffO8zPoN0lspy443XF8U4uYn4NgjJG+9HdrvdzxgT8FWhLMOUI+/lDHWQNE/PYdU2PImPRRtM13OWlbMRcN6hRQ9ybECg+WVok37ohrOwYW4Tj6a2LTrN2k2tTOiFr/hM5upqVvihQc8/smn8w6XTS2ooiC1HwaJw7EKDRFzCMGkIAjSckJuvf1kCOSyewmi+CAFfDlCDHqfBv90E08bS5i5h2XZ5+Tt4vN/dwOm0J/d89VXN3GLR1oU/i7jtkEjA039ZasHZ5SNoX8bx6gj6OxgR1FK//kfxGoUK2MP5Ffg5OgT5JPMfLwOeAd4EuhGFHS5LWHjYwtXRrAH737rcaihsTaR5d6d6PPeySNSVvc9g97wriogwi7QqfFP1IGTVtKj0jlUpu3GBSv54XaPwuwowQFQH5CV0xfybMm2I25LWqOBtI++uKs9ufhPPUPpu7XBf19cldtzzw604hSzxiZTYpykxQX2mOBYIkh53sfmHRxGMDD/DuNCXI1ya7TbBCQzDzkT/KwviQ1LY3bmnF5jRieauV6Y+QO/XZbGCD33LsNXVPWSllbxBlC4MWVCnQwziyn84aEFvJ/1XPGLsjNGpSAR3UP0HphnGzVSXsu78BmCJrFkAipbexRib3BvVS9bmLwONUGYxq1NP69Kc3MGrE0wufrDhmGE+kQmraPZR6pg+dEXCjw6klezw/3CS3oeeFdtLXg02SCb3raMEpuX0s9khLOXSbHR9kAcJHpYub56ilUIilL8lqxRN+zYlA74/q74Tn6HFqh9X/z13iFakXm7sM0wf72I0IqzTCZyA/JE5TNW4kh43xynPSjdZw0kKTpHRSxzSh/Nd/o7rACOr4mjOdKmxWq1nI2NAgtYNK6Xwh8WGSFNF+MzJ2pxu+7vuzm4iMJ0ePsnAOYkANPBqJJhoS1r9Z8UmlT4EfRbsoWNzLSNbh5ehN2Gcj4dE4MIn6WJphPnF+83GoNYVM0JOzfRbl1yCLTQrL1br9sVslur5pknXbD7kv429/ehAe1ErUeLUr9TuC7/K/fH3EwL3Z+U5lmHnp0jS+kEvygBLg0iJyzn0+jxCYXwoA35QoQpy6V/CHrWxL6fdqmfdEU7+os3Crop2LOndria4k4Xcs2Y9ly8Tb+442R98ttPZjhMcL1npDMMfiKKnrH+WGcU98M4cGe7uNmaxFSlH4dFrdrNCIBtTL4tXeteavknnHOtBtUuYnqGF1jDashfQsB26aVdrkTleyENUZIGXWFmlkY6URmfc/ltOa2yupemh5DxQPoE6IykLHpnSM8bQp/ZPDNUr8Kes0ggMfPpvpnntHzFJNt+Nc8d4WS8/FfuNZaVck0qmtHaTOET1TKod7VFA4HS4mgv/9bFd8PjYbsq8ZT3zVihv/kgAc7dqg//yBaNIDK8nKI7eG4lc7lNfQ7TxV//93iYyty7ksjH3c3o7ERFKlu/9HgOQe71mVSCWyMrWOodb9/01KhmCLlw2J/ijVC/W84zckpkEeNdrZ3J92kl5iE19kiz8wtfFVue6n2VMJgeMHuFgdrPpvyBqYKNG5/y7SnETvQhU9UJLGd4sHHmTZZeFxNsp+QzIyhH31Qw29INSRK0BvOZzl6ZhfPS+ILb+imbKwmqLv9ZlEg3jOngzrfAU8N7w6dRwsM0d/wUVNuw5daqB+ArURU9+inbe8W1q0CB7gWwBAYpOZ0ZhSJwde/OhBz54zrlFlI68NSDuE3/1SKrZXBjqfBPta1buj5hFdwu+cFQ1jplZUe19fUerVup0y1zqNTVst30Gl3lUgdyJ//U8dT//QnToGev+9msqKakLyMntTsTSQK2KR1kNCnhdBXWqpZXUmTxHSaZ6aplQ6Jr2vk/eRz/EM91NJzPEU0cquUrrME5L+3A7XKDudb/SrFn55FSgfd6gnWD5qznnVcQqAUR83bISsdkh9thCMn1t9hX2EZ8FL9zH02HLvZSGTtEVUJAxj6vm0gLiyW7oMkEcFUMtO3/evEHDdXpWs5F78b6257sqp2THWOZ8Az5eYhl9IxYcemQ/aiRPCUez0wQ/2nOvu/8m1l9prMkW3F8Na9jx5jS5mLRONt/3xNMn5T6+oDzy4Jh/GTDlwMcVrQj2vXcH4HJVHtPodG9kaY6NtLuUcmeGdbNZhvOwXXfLqxdmz/HoLqdHWpHwcJcY1aR8s6M3jpXtcmiUujf5PqAheiIb7bQcI4dwiSovlWW+df488y1zDzdwzhNhZRv1U8DBt4DWv1zhF/FXg+a1Ivu91esE7uEF47gXFanQRxzCTVcdyCN9qBTByrYsNO+l/wUCow8cHV3TbIqN0ZJzWe92MSboCO/XAbEU7o+MzLUHEEdUNb9OuVtm7qiI4fA6Dy8tkVQWrlKWnyIVGWOynf+2iMGrzLH7LMtkvViSxnAtI+6sL8douGgq4X/0cQXqqN61ZQVbQaQLRxBsxiYNWMq3x35n+12+WQc6YIs05JJZrIlkh1Gfvppyp2+83pLQhQIDvd2GQLxPij4zCY7gNxPxuF/ELrzOcmSOFPdPuOw+70RgculjLchqEu5qVfYN/jHlXy7/w67HG93D1nJJT/1q243TJKQBikZhl9gvpFxj0tWf3xKH3DDawPjcCUlPIKyN/v5+GJTApvIUEErlJe2HwuuBGr++hB6/ckdJkxyC5WGy36yKtJM6I7Yhc0FgtfcqAslqFT8KwQTlw38QbAbJDGfajg5qsOSx3zzjtT+UobFfzaH0pA4+RJuMtH2kDs4D5vYMv3FW+AFhTnwMcAaT9tzwfHSOEBG1/B7+eUICL3H7scZiDXOnKV7fkuGKQHjn+bn0ccMPfKuD7EdBBHI3BE7tMsbYiWOCLdxYEEq5Mf+gtHoIjGGcHZm8yUIfcSecZaW1EgLmUVqr5d8+TSmUZSGx6VBO8QvSItTv73H//uLgCbJFnecXYduLcI6Lcorzc0LgygNZkMvi+/BrwxYacrhz5GVXVQWJflDEfQqitAjcvDrviT3yZjq7+wgPczafvMfrdPPUJk7ga36n4D/Pwz7ZVWBQXYwVw9ltswTAzYec9/4+66XOmv8VM3AOzoK0/suJGrWZf6syx2rgjmvJO3f0Y6f4BrgRl0tT6mxJkuM7H/f500pyHPy3wvhPRGH4cDliPrba0CjtDxNnpJwy+HbCN5xEzji4VzEI9lb0ETvN8Mp8+D9ExADeBF22uvDZZ1tix3SW7gtIWNnF0CyL769wATnc7mlqD+h7QKvskpG8kc7HwmNGqRBlQu58nyEjPGfDK0ExCDFfeWDnlhiEthhEdpCjA8Re3Kgop9nPQkRNpBluuaeEvR63EvUuj5SPtCqm9ThgXUY2XcBa1r7l2a5G0RZX78tzxfbse5dN5rQTO2rpmWF/Q8GQFzgS6DQraecIxnlKmMvvKD3EuYv0LAbRIgaxPFddBDfZj4sw3EdThpfPaieHJcfXcbrzj7ewZM8ZmEpCuXf0uMmR2YLmOwGxd/s5Djdj7ZmhtryApjq/gKa4uIWmPruElrKyNjJx/ZrumApkomv9QCkPxK4KpO3nKky0E73vJH6AhCAGPs0O5850pvK9T+e3qc7V5EmeucwJum/067RjvfGMWEfmZNVRuftMlryuxWMJz6R4o6mz6S/3tzdNvZK27whemoaertt9hGX86ayruMXqQ9lL2bynd5RRL1P/J15XL6sfxFH62SMpsPDg15lda9fTZmtCVg7Sisyrj7F8m1glf7gVLcFWvUKxyd0qM3T3WtKo9fRkKri4nAOpEr/8p5vQnXPynakZ4aKYLLAaNRfmaPJ7v3PNUE1TtxTWIIodlcmFz78lFy2rIcrJNcL2HW1a9GXivMgpbpiM1j35qWbTfT2qJVVl1uVCKQSe+dV1hGF52RWFCnU9t/f50f0jCT32cDm3rX0LdNkfvjwQbt9C7qqx2qIV5IxnyHe25dIWJ9U2si7GlFL36IxrhMUn1suoKccZiR3Yn7vID5ERuq6TXTdt9b5RiiXLcPyU7rTjs/LiSu1+yETjnhy9eRmDtif2HfdpQ/jniYAZ9Y8uMcCUM5demHO1EitD4qacxnvK68rVAxh72lbrGFbuia09H3k8j8uc6kKE44Tov5Zthu2Ej3M7x25Gtnj5wIXq7SOXE5M7/R44SuczzunBNb0RRnNFUhD3+XMVPWJfORmyeX6I+V+5twL3uc4UZ+o0lm4hzzymYauOXzzmWVFd35OZ+kufqwm4v096djcTZz9pA1I3xHkhLlPHyLoWNiCdR/prlD+e4OY/thV9Djoel+9N6rBFeEn6tstpgBH81mHUBfeudt8w94hh//30nP1MXezmyaqPC8LyWHR3sBvC2JPoZTP3gzz3ku8jMBsz2IMjp0+sl3yExVCv+Q3d7QiLV/450lL3Vps60j98qfe+W65B63XCfUYRKZI92Tmm4vk9rualLZ72I+YfmwpDWOqInc0cugwOGN9mDfDqpWy4y+kNXg9z4YEG1oDIzdeNyYU/5+w5vDFEo5/FK3yYiqKbG5pnW9z5RBc4eBC6tpjO2LKfz4W7vIjVRgkovDJYR23/Tl+jeJ/3QGnuvbUPPWvRcyWMfc6RfSmT3ygWuxeC+JLfFz76cxWkc+EFcjWmPsReFUtfFcsFcgW2yD7LlYiE92TLG5aC+ZozfHLWR7A/Kc3zpZ2GK4uam5r+fRSwmllaBubk4KJjYgbMxCQjtJmSBF3qQupDqPyyBSAP4miDMYiu/IvopwzjfeYoopIU6Bjnwz9YFBlVSA66vCnCBy5ajKrqggibqgieqVOQ89GBoaAt/0t+1iib04Z4obX1+wDP9CukgOeOLkSo8QENcJbhnyRB+cPADk+yrpmnZEumdGHrrxFIlz9txySkteTvhkQjxroSyFxJFWdi/cecLTq/z4iKOW3838KS9ayXNVdT2k1QyIXnnv+RjdnQ0LulGaAdTcP2EqJnim1WvxOP09YbWvu5YfbK7o+H3Jkz52947Zh+w9aD28EDUKNt5qBSnYg8U2xotNqigBZ+TnKz7VDD8+hTtdCYKTutQsiYXPNf1gNSctya8PcZ1XoWFlArtboQVFRUdc3NwRuttoGBgSBtbeyBkY3QbR0dAaGdEG4eHgJtzZDE7av8VanQRRBu/cqR9LfPz790dXVvX+D9env//YHa/x07ElhXRx8GAx8YFiYWFhERkpamFhYZGVgU5CYmLuUXNegWFisbVDRoJCYjE9zUxDzawhRsJUo1+tQBsvbrWm7wITii7j9yibCQikGx0elJv/MqJTHZmaCqqs643GywNVdHAjIyCCiHBnw+wH9Q99D5dXV/IiIl8oraYCQkJ/Jq6LHGxynzCrp+U1JV5lVUgFtUWO7pTPGYlQPgm1/O8659eBZXWP4JCiIxs7AKOjoy3VaO5xWWYK9rYuYXFkNmWwYvQ1zNbsdIaEI43XbmNTYidXB65pV+EDw+P/cnksnuvj2c3B7E8vVHotHtpur6vIHUQAG3Hj27JDQEs54wiWv6EpBmxTMWzRRW8k4DUMWHh0lJSYf3qdtBCnxk0w5rGtUcqOFac9n7D9nCBmnA99oJ9wZ22wN3cwr32qW6yMQL7kBgfEQmavLKQ/vwfRSDuH18JkoaZNXU1FY9YqJMWxYSeUQDuhcHjfz4N8EPgvd+l/PwWK/hTabz7A04pvnvI7Qa1yepa+GC3JyYSyYGg3leQ+BN/lQZ+bm/DmQJuWMhW+nzxSN50Bgm04dT0Ojpb4mhTTk0w46nhrAbVyObylgfD9wXSdgvYbGWa3U7XaqbmoqKDhNIHsjBN/8k7PVm/+KOHbRd/2f/yBSH7UhKJ4cdcKL/eTyVGURbn9YTBKoJf8CT7jbYuy3AaIWQYI47Vtc7E8sE4zORok/HEOm9FsvE7dMmKSV4m++Gm/qF8uZzMhVgkogtiSr7/RiCd02OXjvc+0ALueMboX8XdOSjhPZzfsgnElb38NjVjgBaLuQZI4LmVpdhgcBvWp9eS/TP/0CGgcbtEL/nBwSWbdm9+KA9Gx9BceBM9dCjw0rRjXhNLhzTQMyNuMd2SQ9Iue/pdbzduGO50sy6wCNHsLBAUqn+8sEEVv3czofhyX/78Lf/Wxu7G5rEwerVN8HdDU/a/dmTFtoPxoCzV6N2bBZsEHASA9XWC9eMc1oIyVm63rTPMxkgesYNW5S63RF1uc43y2xrQ+jCu3IXnTb8j0504MWq9FZw7/fnmSXxdyaP5/MN2m7oeID4NMLCWOOrbfvVxgvBeo/2mV/KZv4KfjsQnjVutjIaWNTaac64XtkR+sFMFHVrLmJoaBgm8m0a1c8ZxnXHIURpFcBMIi4mpwUPWYFFIP3kKKa0/Z84ZSa+ojJmBEuxGF7T7SWanA8/JmUT+Ocs5RbsV49Z2TmuGGc3zl867IA/A0xxenZQCVEzAsvt1nIFDyhG2TuwR6mu/9L7eNtiP+csAq/kTJvAFKSmBSvOwMQaZ0PQJ6jiYrxE5/FYsG5FIT5nvQO9ZgNHgdww3dMOt6NH6NwuqWRfsjzeWLNLAOG39NERJQ5dOA3V64AUftYyrTLQgwv5olpzE5foRzYaamrx3IXhYfDLS5t4HzLMk93T0z/Prpu96c88W/E34V+y8PCyYe2GsHdlxG3b4NAX+CHAM9H33F9F8OO/bBBC7wXbuf/AQobExcn9gYcPJdbBLxIKwvdlhjIwNCRgIMBISEggIAJLXjQSExcPXkxiPowsEazppkDm0g38Dc81+tAGRuIjE3d28Fv9F64c5jH80ByBHAYWFMs=
*/