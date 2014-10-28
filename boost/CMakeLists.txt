macro(lyx_add_path _list _prefix)
	set(_tmp)
	foreach(_current ${${_list}})
		set(_tmp ${_tmp} ${_prefix}/${_current})
	endforeach(_current)
	set(${_list} ${_tmp})
endmacro(lyx_add_path _out _prefix)

add_subdirectory(regex)

