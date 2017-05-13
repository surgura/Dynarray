# Dynarray
N-dimensional array with static runtime size.

# Requirements
C++14 is required.

# Example usage
```c++
Dynarray<2, float> someArray(10, 15);
someArray.At(2,9) = 15.0654;
```

# Feature request
If you miss a feature, make an issue.

# TODO list
- Access by array operator. Pretty hard, so don't expect this anytime soon.
