{ stdenv, fetchFromGitHub, cmake, ninja, rapidjson, llvmPackages_13
}:

let
  libllvm = llvmPackages_13.tools.libllvm;
in
stdenv.mkDerivation {
  name = "libBlockchain";
  version = "0.0.1";

  src = ./.;

  postPatch = ''
    # Remove local rapidjson in favor of nix-provided rapidjson
    sed -i 's|../rapidjson|rapidjson|' lib/include/*.h
    rm -rf lib/rapidjson/
  '';

  nativeBuildInputs = [ cmake ninja libllvm ];
  propagatedBuildInputs = [ rapidjson ];

  LLVM_DIR="${libllvm}";

  outputs = [ "out" "dev" ];

  # avoid CMake split derivation errors with `nix develop`
  outputInclude = "out";
  postFixup = ''
    moveToOutput include "$dev"
    substituteInPlace "$dev"/lib/cmake/libBlockchain/libBlockchainTargets.cmake \
      --replace "$out"/include "$dev"/include
  '';
}
