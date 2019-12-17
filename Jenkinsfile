pipeline {
  agent any
  stages {
    stage('Build All Projects') {
      steps {
        sh 'make -C Project/'
      }
    }

    stage('Archive Artifacts') {
      steps {
        archiveArtifacts(artifacts: '**/*.hex,**/*.elf,**/*.bin', fingerprint: true)
      }
    }

  }
}