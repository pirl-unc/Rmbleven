test_that("mbleven_compare works", {
  expect_equal(mbleven_compare('aaa', 'aaa'), 0)
  expect_equal(mbleven_compare('aaa', 'aab'), 1)
  expect_equal(mbleven_compare('aaa', 'abb'), 2)
  expect_equal(mbleven_compare('aaa', 'bbb'), -1)
})
