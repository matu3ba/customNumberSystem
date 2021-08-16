const std = @import("std");
const print = std.debug.print;
const assert = std.debug.assert;

// base is base of number system
// mem[] is the number in the base number system
// we do not need to use length of the buffer as function arguments

// NOTE
// - This pattern is, because mem_arrray is actually an array
//    var mem_array = [_]u32{ 1, 2, 3 };
//    var mem_ref: []u32 = &mem_array;
// - TODO error handling instead of returning u32

//assume base >= 0
fn isValidNumber(mem: []u32, base: u32) bool {
    for (mem) |m_el| {
        if (m_el >= base)
            return false;
    }
    return true;
}

fn isNotNull(mem: []const u32) bool {
    for (mem) |m_el| {
        if (m_el != 0) {
            return true;
        }
    }
    return false;
}

// TODO define error codes
fn add(mem: []u32, base: u32) u32 {
    var carry = false;
    var index: u32 = @intCast(u32, mem.len - 1);
    while (index >= 0) : (index -= 1) {
        var added_val = mem[index] + 1;
        if (added_val == base) {
            carry = true;
        } else {
            mem[index] = added_val;
            break;
        }
    }
    if (index == -1 and carry == true) {
        return 1; // could not increase anymore
    }

    if (carry == true) {
        assert(index < mem.len - 1);
        index += 1; // zero out numbers right of the index
        while (index < mem.len) : (index += 1) {
            mem[index] = 0;
        }
    }
    return 0;
}

test "isValidNumber" {
    const base: u32 = 4;
    var mem_array = [_]u32{ 1, 2, 3 };
    var mem_ref: []u32 = &mem_array;
    assert(isValidNumber(mem_ref, base) == true);
}

test "isNull" {
    var mem_array1 = [_]u32{ 0, 0, 0 };
    var mem_ref1: []u32 = &mem_array1;
    var is_not_null = isNotNull(mem_ref1);
    assert(is_not_null == false);

    var mem_array2 = [_]u32{ 1, 1, 1 };
    var mem_ref2: []u32 = &mem_array2;
    assert(isNotNull(mem_ref2) == true);
}

test "add" {
    const base: u32 = 4;
    var mem_array = [_]u32{ 1, 2, 3 };
    var mem_ref: []u32 = &mem_array;
    _ = add(mem_ref, base);
    //assert(add(mem_ref, base) == true);
    // TODO deep copy of stuff
}
