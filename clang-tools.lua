#!/usr/bin/env lua
-- clang-tools.lua
-- @author Dante Harper

local args = {}
for _, v in ipairs(arg) do
  args[v] = true
end

local do_format = args["-f"] or next(args) == nil
local do_tidy   = args["-t"] or next(args) == nil
local do_fix    = args["-i"] or false

-- Function to run a command
local function run_cmd(cmd)
  print("> " .. cmd)
  local ok, exit_type, code = os.execute(cmd)
  if not ok or (exit_type ~= "exit" or code ~= 0) then
    print(string.format("Command failed (type: %s, code: %s)", tostring(exit_type), tostring(code)))
    os.exit(1)
  end
end

if do_format and do_fix then
  run_cmd("find ./src -iname \"*.cpp\" -o -iname \"*.h\" -o -iname \"*.hpp\" -o -iname \"*.c\" -o -iname \"*.inl\" | xargs clang-format -i --verbose")
elseif do_format then
  run_cmd("find ./src -iname \"*.cpp\" -o -iname \"*.h\" -o -iname \"*.hpp\" -o -iname \"*.c\" -o -iname \"*.inl\" | xargs clang-format -n --verbose")
end

if do_tidy and do_fix then
  run_cmd("find ./src -iname \"*.cpp\" -o -iname \"*.h\" -o -iname \"*.hpp\" -o -iname \"*.c\" | xargs clang-tidy -i")
elseif do_tidy then
  run_cmd("find ./src -iname \"*.cpp\" -o -iname \"*.h\" -o -iname \"*.hpp\" -o -iname \"*.c\" | xargs clang-tidy")
end
