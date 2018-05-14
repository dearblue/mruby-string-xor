assert("String#^(other)") do
  assert_equal("\0" * 12, 'わーい！' ^ 'わーい！')
end

assert("String#xor_clamp") do
  src = 'abcdefghijklmnopqrstuvwxyz' * 1 # duplicate unshared string
  assert_equal('AbCdefghijklmnopqrstuvwxyz', src.xor_clamp("\x20\x00\x20"))
  assert_equal('AbCDeFGhIJkLMnOpqrstuvwxyz', src.xor_clamp("\x20\x00\x20" * 5))
  assert_equal('AbCDeFGhIJkLMnOPqRStUVwXYz', src.xor_clamp("\x20\x00\x20" * 100))
  assert_equal('abcdefghijklmnopqrstuvwxyz', src)
end

assert("String#xor_repeat") do
  src = 'abcdefghijklmnopqrstuvwxyz' * 1 # duplicate unshared string
  assert_equal('AbCDeFGhIJkLMnOPqRStUVwXYz', src.xor_repeat("\x20\x00\x20"))
  assert_equal('AbCDeFGhIJkLMnOPqRStUVwXYz', src.xor_repeat("\x20\x00\x20" * 100))
  assert_equal('abcdefghijklmnopqrstuvwxyz', src)
end
