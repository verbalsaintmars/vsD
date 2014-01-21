# ******************************
# Copyleft 2014 Verbalsaint
# ******************************

set(DIRS lib header config ${MODULES_PATH})

# file(MAKE_DIRECTORY "${BIN_DIR}")
# file(MAKE_DIRECTORY "${TEST_BIN_DIR}")

foreach(ddir ${DIRS})
   file(MAKE_DIRECTORY "${BIN_DIR}/${ddir}")
   file(MAKE_DIRECTORY "${TEST_BIN_DIR}/${ddir}")
endforeach(ddir)
