$ErrorActionPreference = 'Stop'
$root = Get-Location

$paths = & git -C $root ls-files --cached --others --exclude-standard
if ($LASTEXITCODE -ne 0) { throw 'Unable to list repository files with Git.' }

$paths |
  ForEach-Object { $_ -replace '\\', '/' } |
  Sort-Object |
  ConvertTo-Json |
  Set-Content -Path (Join-Path $root 'solutions.json') -Encoding utf8

Write-Host "Indexed $($paths.Count) files in solutions.json"