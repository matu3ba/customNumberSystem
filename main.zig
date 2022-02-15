const std = @import("std");
const print = std.debug.print;
const testing = std.testing;
const assert = std.debug.assert;

// base is base of number system
// mem[] is the number in the base number system
// we do not need to use length of the buffer as function arguments

// NOTE
// - This pattern is, because mem_arrray is actually an array
//    var mem_array = [_]u32{ 1, 2, 3 };
//    var mem_ref: []u32 = &mem_array;
//    * For convenienc we use &mem_array directly

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

// on successfull addition return true, otherwise false
fn add(mem: []u32, base: u32) bool {
    var carry = false;
    var index: u32 = @intCast(u32, mem.len - 1);
    while (index > 0) : (index -= 1) {
        var added_val = mem[index] + 1;
        if (added_val == base) {
            carry = true;
        } else {
            mem[index] = added_val;
            break;
        }
    }
    // prevent index underflow
    if (index == 0 and carry == true and mem[index] + 1 == base) {
        return false; // could not increase anymore
    }
    // zero out numbers right of the index
    if (carry == true) {
        assert(index < mem.len - 1);
        index += 1;
        while (index < mem.len) : (index += 1) {
            mem[index] = 0;
        }
    }
    return true;
}

test "isValidNumber" {
    const base: u32 = 4;
    var mem_array = [_]u32{ 1, 2, 3 };
    var is_val_nr = isValidNumber(&mem_array, base);
    try testing.expectEqual(true, is_val_nr);
}

test "isNull" {
    var mem_array1 = [_]u32{ 0, 0, 0 };
    var is_not_null = isNotNull(&mem_array1);
    try testing.expectEqual(false, is_not_null);

    var mem_array2 = [_]u32{ 1, 1, 1 };
    is_not_null = isNotNull(&mem_array2);
    try testing.expectEqual(true, is_not_null);
}

test "add" {
    const base: u32 = 4;
    var mem_array = [_]u32{ 1, 2, 3 };
    const result = add(&mem_array, base);
    const exp_mem_array = [_]u32{ 1, 3, 0 };
    try testing.expectEqual(exp_mem_array, mem_array);
    try testing.expectEqual(true, result);

    mem_array = [_]u32{ 3, 3, 3 };
    const result2 = add(&mem_array, base);
    try testing.expectEqual(mem_array, mem_array);
    try testing.expectEqual(false, result2);
}
