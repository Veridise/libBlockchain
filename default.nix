{ stdenv, fetchFromGitHub, cmake, ninja, rapidjson, llvmPackages_13
}:

let
  libllvm = llvmPackages_13.tools.libllvm;
in
stdenv.mkDerivation {
  name = "libBlockchain";
  version = "0.0.1";

  src = ./.;

  nativeBuildInputs = [ cmake ninja libllvm ];
  propagatedBuildInputs = [ rapidjson ];

  LLVM_DIR="${libllvm}";

  outputs = [ "out" "dev" ];

  postPatch = ''
    sed -i 's|../rapidjson|rapidjson|' lib/include/*.h
    rm -rf lib/rapidjson/
  '';
}
