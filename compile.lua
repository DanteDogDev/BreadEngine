#!/usr/bin/env lua
-- compile.lua
-- @author Xein

local build_dir = "./bin/debug"
local build_type = "Debug"
local generator = "Unix Makefiles"
local c_compiler = "gcc"
local cpp_compiler = "g++"
local compile_commands_src = build_dir .. "/compile_commands.json"
local compile_commands_dst = "./compile_commands.json"

local args = {}
for _, v in ipairs(arg) do
  args[v] = true
end

local do_release  = args["-r"] or false

if do_release then
  build_dir = "./bin/release"
  build_type = "Release"
end

-- Function to run a command
local function run_cmd(cmd)
  print("> " .. cmd)
  local ok, exit_type, code = os.execute(cmd)
  if not ok or (exit_type ~= "exit" or code ~= 0) then
    print(string.format("Command failed (type: %s, code: %s)", tostring(exit_type), tostring(code)))
    os.exit(1)
  end
end

-- Function to copy compile_commands.json
local function copy_compile_commands()
  print("\n=== Copying compile_commands.json ===")
  run_cmd(string.format('cp "%s" "%s"', compile_commands_src, compile_commands_dst))
end


-- Generate step
print("\n=== Generating build system ===")
run_cmd(string.format(
  'cmake -S . -B "%s" -G "%s" -DCMAKE_BUILD_TYPE=%s -DCMAKE_C_COMPILER=%s -DCMAKE_CXX_COMPILER=%s',
  build_dir, generator, build_type, c_compiler, cpp_compiler
))
copy_compile_commands()

-- Build step
print("\n=== Building project ===")
run_cmd(string.format('cmake --build "%s"', build_dir))
