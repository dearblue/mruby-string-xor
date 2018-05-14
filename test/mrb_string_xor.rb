assert("String#^(other)") do
  src = 'わーい！' * 3
  assert_equal("\0" * src.bytesize, src ^ 'わーい！' * 3)
  assert_equal(src, 'わーい！' * 3)
end
