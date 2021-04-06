Get-ChildItem | Where-Object { 
        $_.Name -in 'ScreamingBird.sln','ScreamingBird.vcxproj','ScreamingBird.vcxproj.filters','ScreamingBird.vcxproj.user','.qmake.stash', 'debug','release'
    } | Remove-Item -Force
