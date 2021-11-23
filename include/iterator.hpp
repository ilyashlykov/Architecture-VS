/* Image iterator.
 * @file
 * @date 2018-08-05
 * @author Anonymous
 */
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cmath>
#include <iterator>
#include <type_traits>
#include <utility>
#include <boost/iterator/iterator_adaptor.hpp>
using namespace std;

//{ image iterator
template<class Iterator>
class image_iterator : public boost::iterator_adaptor<image_iterator<Iterator>, Iterator>
{
private:
    int width;
    int stride;
    int dif;
    int bias;
public:
    image_iterator(Iterator it, size_t image_width, size_t image_stride) : boost::iterator_adaptor<image_iterator<Iterator>, Iterator>(it) {
        width = image_width;
        stride = image_stride;
        dif = image_stride - image_width;
        bias = 0;
    }

    void increment() {
        if (bias < width - 1) {
            bias++;
            (this->base_reference())++;
        }
        else {
            bias = 0;
            this->base_reference() += dif + 1;
        }
    }

    void decrement() {
        if (bias > 0) {
            bias-=1;
            (this->base_reference())--;
        }
        else {
            bias = width - 1;
            this->base_reference() -= dif + 1;
        }
    }

    void advance(typename boost::iterator_adaptor<image_iterator<Iterator>, Iterator>::difference_type n) {
        int row = floor((bias + n) / width);
        int col = bias + n - row * width;
        this->base_reference() += -bias + row * stride + col;
        bias = col;

    }

    typename boost::iterator_adaptor<image_iterator<Iterator>, Iterator>::difference_type distance_to(const image_iterator& iter) const
    {
      size_t dist = ((iter.base_reference() - iter.bias) - (this->base_reference() - bias)) / static_cast<ptrdiff_t>(stride)* width + (iter.bias - bias);
      return dist;
    }

};
//}

#endif // ITERATOR_HPP
