{
  inputs = {
    flake-utils.url = "github:numtide/flake-utils/v1.0.0";
  };

  outputs = { self, nixpkgs, flake-utils }: {
    overlays.default = final: prev: {
      libBlockchain = with final; callPackage ./libBlockchain.nix {};
    };

    packages = flake-utils.lib.eachDefaultSystemMap (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [ self.overlays.default ];
        };
      in
    {
      libBlockchain = pkgs.libBlockchain;
      default = pkgs.libBlockchain;
    });
  };
}